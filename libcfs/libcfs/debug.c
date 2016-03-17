/*
 * GPL HEADER START
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 only,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License version 2 for more details (a copy is included
 * in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; If not, see
 * http://www.sun.com/software/products/lustre/docs/GPLv2.pdf
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 *
 * GPL HEADER END
 */
/*
 * Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright (c) 2011, 2014, Intel Corporation.
 */
/*
 * This file is part of Lustre, http://www.lustre.org/
 * Lustre is a trademark of Sun Microsystems, Inc.
 *
 * libcfs/libcfs/debug.c
 *
 * Author: Phil Schwan <phil@clusterfs.com>
 *
 */

# define DEBUG_SUBSYSTEM S_LNET

#include <linux/kthread.h>
#include <libcfs/libcfs.h>
#include "tracefile.h"

static char debug_file_name[1024];

unsigned int libcfs_subsystem_debug = ~0;
CFS_MODULE_PARM(libcfs_subsystem_debug, "i", int, 0644,
                "Lustre kernel debug subsystem mask");
EXPORT_SYMBOL(libcfs_subsystem_debug);

unsigned int libcfs_debug = (D_CANTMASK |
			     D_NETERROR | D_HA | D_CONFIG | D_IOCTL | D_LFSCK);
CFS_MODULE_PARM(libcfs_debug, "i", int, 0644,
                "Lustre kernel debug mask");
EXPORT_SYMBOL(libcfs_debug);

unsigned int libcfs_debug_mb;
CFS_MODULE_PARM(libcfs_debug_mb, "i", uint, 0644,
                "Total debug buffer size.");

unsigned int libcfs_printk = D_CANTMASK;
CFS_MODULE_PARM(libcfs_printk, "i", uint, 0644,
                "Lustre kernel debug console mask");

unsigned int libcfs_console_ratelimit = 1;
CFS_MODULE_PARM(libcfs_console_ratelimit, "i", uint, 0644,
                "Lustre kernel debug console ratelimit (0 to disable)");

unsigned int libcfs_console_max_delay;
CFS_MODULE_PARM(libcfs_console_max_delay, "l", uint, 0644,
                "Lustre kernel debug console max delay (jiffies)");

unsigned int libcfs_console_min_delay;
CFS_MODULE_PARM(libcfs_console_min_delay, "l", uint, 0644,
                "Lustre kernel debug console min delay (jiffies)");

unsigned int libcfs_console_backoff = CDEBUG_DEFAULT_BACKOFF;
CFS_MODULE_PARM(libcfs_console_backoff, "i", uint, 0644,
                "Lustre kernel debug console backoff factor");

unsigned int libcfs_debug_binary = 1;

unsigned int libcfs_stack = 3 * THREAD_SIZE / 4;
EXPORT_SYMBOL(libcfs_stack);

unsigned int libcfs_catastrophe;
EXPORT_SYMBOL(libcfs_catastrophe);

unsigned int libcfs_watchdog_ratelimit = 300;

unsigned int libcfs_panic_on_lbug = 1;
CFS_MODULE_PARM(libcfs_panic_on_lbug, "i", uint, 0644,
                "Lustre kernel panic on LBUG");

atomic_t libcfs_kmemory = ATOMIC_INIT(0);
EXPORT_SYMBOL(libcfs_kmemory);

static wait_queue_head_t debug_ctlwq;

char libcfs_debug_file_path_arr[PATH_MAX] = LIBCFS_DEBUG_FILE_PATH_DEFAULT;

/* We need to pass a pointer here, but elsewhere this must be a const */
static char *libcfs_debug_file_path;
CFS_MODULE_PARM(libcfs_debug_file_path, "s", charp, 0644,
                "Path for dumping debug logs, "
                "set 'NONE' to prevent log dumping");

int libcfs_panic_in_progress;

/* libcfs_debug_token2mask() expects the returned
 * string in lower-case */
static const char *libcfs_debug_subsys2str(int subsys)
{
	static const char *libcfs_debug_subsystems[] = LIBCFS_DEBUG_SUBSYS_NAMES;

	if (subsys >= ARRAY_SIZE(libcfs_debug_subsystems))
		return NULL;

	return libcfs_debug_subsystems[subsys];
}

/* libcfs_debug_token2mask() expects the returned
 * string in lower-case */
static const char *libcfs_debug_dbg2str(int debug)
{
	static const char *libcfs_debug_masks[] = LIBCFS_DEBUG_MASKS_NAMES;

	if (debug >= ARRAY_SIZE(libcfs_debug_masks))
		return NULL;

	return libcfs_debug_masks[debug];
}

int
libcfs_debug_mask2str(char *str, int size, int mask, int is_subsys)
{
        const char *(*fn)(int bit) = is_subsys ? libcfs_debug_subsys2str :
                                                 libcfs_debug_dbg2str;
        int           len = 0;
        const char   *token;
        int           i;

        if (mask == 0) {                        /* "0" */
                if (size > 0)
                        str[0] = '0';
                len = 1;
        } else {                                /* space-separated tokens */
                for (i = 0; i < 32; i++) {
                        if ((mask & (1 << i)) == 0)
                                continue;

                        token = fn(i);
                        if (token == NULL)              /* unused bit */
                                continue;

                        if (len > 0) {                  /* separator? */
                                if (len < size)
                                        str[len] = ' ';
                                len++;
                        }

                        while (*token != 0) {
                                if (len < size)
                                        str[len] = *token;
                                token++;
                                len++;
                        }
                }
        }

        /* terminate 'str' */
        if (len < size)
                str[len] = 0;
        else
                str[size - 1] = 0;

        return len;
}

int
libcfs_debug_str2mask(int *mask, const char *str, int is_subsys)
{
        const char *(*fn)(int bit) = is_subsys ? libcfs_debug_subsys2str :
                                                 libcfs_debug_dbg2str;
        int         m = 0;
        int         matched;
        int         n;
        int         t;

        /* Allow a number for backwards compatibility */

        for (n = strlen(str); n > 0; n--)
                if (!isspace(str[n-1]))
                        break;
        matched = n;

        if ((t = sscanf(str, "%i%n", &m, &matched)) >= 1 &&
            matched == n) {
                /* don't print warning for lctl set_param debug=0 or -1 */
                if (m != 0 && m != -1)
                        CWARN("You are trying to use a numerical value for the "
                              "mask - this will be deprecated in a future "
                              "release.\n");
                *mask = m;
                return 0;
        }

        return cfs_str2mask(str, fn, mask, is_subsys ? 0 : D_CANTMASK,
                            0xffffffff);
}

/**
 * Dump Lustre log to ::debug_file_path by calling tracefile_dump_all_pages()
 */
void libcfs_debug_dumplog_internal(void *arg)
{
	static time_t last_dump_time;
	time_t current_time;
	void *journal_info;

	journal_info = current->journal_info;
	current->journal_info = NULL;

	current_time = cfs_time_current_sec();

	if (strncmp(libcfs_debug_file_path_arr, "NONE", 4) != 0 &&
	    current_time > last_dump_time) {
		last_dump_time = current_time;
		snprintf(debug_file_name, sizeof(debug_file_name) - 1,
			 "%s.%ld." LPLD, libcfs_debug_file_path_arr,
			 current_time, (long_ptr_t)arg);
		printk(KERN_ALERT "LustreError: dumping log to %s\n",
		       debug_file_name);
		cfs_tracefile_dump_all_pages(debug_file_name);
		libcfs_run_debug_log_upcall(debug_file_name);
	}
	current->journal_info = journal_info;
}

static int libcfs_debug_dumplog_thread(void *arg)
{
	libcfs_debug_dumplog_internal(arg);
	wake_up(&debug_ctlwq);
	return 0;
}

void libcfs_debug_dumplog(void)
{
	wait_queue_t wait;
	struct task_struct    *dumper;
	ENTRY;

	/* we're being careful to ensure that the kernel thread is
	 * able to set our state to running as it exits before we
	 * get to schedule() */
	init_waitqueue_entry(&wait, current);
	set_current_state(TASK_INTERRUPTIBLE);
	add_wait_queue(&debug_ctlwq, &wait);

	dumper = kthread_run(libcfs_debug_dumplog_thread,
			     (void *)(long)current_pid(),
			     "libcfs_debug_dumper");
	if (IS_ERR(dumper))
		printk(KERN_ERR "LustreError: cannot start log dump thread:"
		       " %ld\n", PTR_ERR(dumper));
	else
		schedule();

	/* be sure to teardown if cfs_create_thread() failed */
	remove_wait_queue(&debug_ctlwq, &wait);
	set_current_state(TASK_RUNNING);
}
EXPORT_SYMBOL(libcfs_debug_dumplog);

int libcfs_debug_init(unsigned long bufsize)
{
	int    rc = 0;
	unsigned int max = libcfs_debug_mb;

	init_waitqueue_head(&debug_ctlwq);

	if (libcfs_console_max_delay <= 0 || /* not set by user or */
	    libcfs_console_min_delay <= 0 || /* set to invalid values */
	    libcfs_console_min_delay >= libcfs_console_max_delay) {
		libcfs_console_max_delay = CDEBUG_DEFAULT_MAX_DELAY;
		libcfs_console_min_delay = CDEBUG_DEFAULT_MIN_DELAY;
	}

	if (libcfs_debug_file_path != NULL) {
		strlcpy(libcfs_debug_file_path_arr,
			libcfs_debug_file_path,
			sizeof(libcfs_debug_file_path_arr));
	}

	/* If libcfs_debug_mb is set to an invalid value or uninitialized
	 * then just make the total buffers smp_num_cpus * TCD_MAX_PAGES */
	if (max > cfs_trace_max_debug_mb() || max < num_possible_cpus()) {
		max = TCD_MAX_PAGES;
	} else {
		max = (max / num_possible_cpus());
		max = (max << (20 - PAGE_CACHE_SHIFT));
	}
	rc = cfs_tracefile_init(max);

        if (rc == 0)
                libcfs_register_panic_notifier();

        return rc;
}

int libcfs_debug_cleanup(void)
{
        libcfs_unregister_panic_notifier();
        cfs_tracefile_exit();
        return 0;
}

int libcfs_debug_clear_buffer(void)
{
        cfs_trace_flush_pages();
        return 0;
}

/* Debug markers, although printed by S_LNET
 * should not be be marked as such. */
#undef DEBUG_SUBSYSTEM
#define DEBUG_SUBSYSTEM S_UNDEFINED
int libcfs_debug_mark_buffer(const char *text)
{
        CDEBUG(D_TRACE,"***************************************************\n");
        LCONSOLE(D_WARNING, "DEBUG MARKER: %s\n", text);
        CDEBUG(D_TRACE,"***************************************************\n");

        return 0;
}
#undef DEBUG_SUBSYSTEM
#define DEBUG_SUBSYSTEM S_LNET

void libcfs_debug_set_level(unsigned int debug_level)
{
	printk(KERN_WARNING "Lustre: Setting portals debug level to %08x\n",
	       debug_level);
	libcfs_debug = debug_level;
}

long libcfs_log_return(struct libcfs_debug_msg_data *msgdata, long rc)
{
        libcfs_debug_msg(msgdata, "Process leaving (rc=%lu : %ld : %lx)\n",
                         rc, rc, rc);
        return rc;
}
EXPORT_SYMBOL(libcfs_log_return);

void libcfs_log_goto(struct libcfs_debug_msg_data *msgdata, const char *label,
                     long_ptr_t rc)
{
        libcfs_debug_msg(msgdata, "Process leaving via %s (rc=" LPLU " : " LPLD
                         " : " LPLX ")\n", label, (ulong_ptr_t)rc, rc, rc);
}
EXPORT_SYMBOL(libcfs_log_goto);
