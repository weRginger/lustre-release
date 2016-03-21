/*
 * include/linux/htree_lock.h
 *
 * Copyright (c) 2011, 2012, Intel Corporation.
 *
 * Author: Liang Zhen <liang@whamcloud.com>
 */

/*
 * htree lock
 *
 * htree_lock is an advanced lock, it can support five lock modes (concept is
 * taken from DLM) and it's a sleeping lock.
 *
 * most common use case is:
 * - create a htree_lock_head for data
 * - each thread (contender) creates it's own htree_lock
 * - contender needs to call htree_lock(lock_node, mode) to protect data and
 *   call htree_unlock to release lock
 *
 * Also, there is advanced use-case which is more complex, user can have
 * PW/PR lock on particular key, it's mostly used while user holding shared
 * lock on the htree (CW, CR)
 *
 * htree_lock(lock_node, HTREE_LOCK_CR); lock the htree with CR
 * htree_node_lock(lock_node, HTREE_LOCK_PR, key...); lock @key with PR
 * ...
 * htree_node_unlock(lock_node);; unlock the key
 *
 * Another tip is, we can have N-levels of this kind of keys, all we need to
 * do is specifying N-levels while creating htree_lock_head, then we can
 * lock/unlock a specific level by:
 * htree_node_lock(lock_node, mode1, key1, level1...);
 * do something;
 * htree_node_lock(lock_node, mode1, key2, level2...);
 * do something;
 * htree_node_unlock(lock_node, level2);
 * htree_node_unlock(lock_node, level1);
 *
 * NB: for multi-level, should be careful about locking order to avoid deadlock
 */

#ifndef _LINUX_HTREE_LOCK_H
#define _LINUX_HTREE_LOCK_H

#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/sched.h>

/*
 * Lock Modes
 * more details can be found here:
 * http://en.wikipedia.org/wiki/Distributed_lock_manager
 */
typedef enum {
	HTREE_LOCK_EX	= 0, /* exclusive lock: incompatible with all others */
	HTREE_LOCK_PW,	     /* protected write: allows only CR users */
	HTREE_LOCK_PR,	     /* protected read: allow PR, CR users */
	HTREE_LOCK_CW,	     /* concurrent write: allow CR, CW users */
	HTREE_LOCK_CR,	     /* concurrent read: allow all but EX users */
	HTREE_LOCK_MAX,	     /* number of lock modes */
} htree_lock_mode_t;

#define HTREE_LOCK_NL		HTREE_LOCK_MAX
#define HTREE_LOCK_INVAL	0xdead10c

enum {
	HTREE_HBITS_MIN		= 2,
	HTREE_HBITS_DEF		= 14,
	HTREE_HBITS_MAX		= 32,
};

enum {
	HTREE_EVENT_DISABLE	= (0),
	HTREE_EVENT_RD		= (1 << HTREE_LOCK_PR),
	HTREE_EVENT_WR		= (1 << HTREE_LOCK_PW),
	HTREE_EVENT_RDWR	= (HTREE_EVENT_RD | HTREE_EVENT_WR),
};

struct htree_lock;

typedef void (*htree_event_cb_t)(void *target, void *event);

struct htree_lock_child {
	struct list_head	lc_list;	/* granted list */
	htree_event_cb_t	lc_callback;	/* event callback */
	unsigned		lc_events;	/* event types */
};

struct htree_lock_head {
	unsigned long		lh_lock;	/* bits lock */
	/* blocked lock list (htree_lock) */
	struct list_head	lh_blocked_list;
	/* # key levels */
	u16			lh_depth;
	/* hash bits for key and limit number of locks */
	u16			lh_hbits;
	/* counters for blocked locks */
	u16			lh_nblocked[HTREE_LOCK_MAX];
	/* counters for granted locks */
	u16			lh_ngranted[HTREE_LOCK_MAX];
	/* private data */
	void			*lh_private;
	/* array of children locks */
	struct htree_lock_child	lh_children[0];
};

/* htree_lock_node_t is child-lock for a specific key (ln_value) */
struct htree_lock_node {
	htree_lock_mode_t	ln_mode;
	/* major hash key */
	u16			ln_major_key;
	/* minor hash key */
	u16			ln_minor_key;
	struct list_head	ln_major_list;
	struct list_head	ln_minor_list;
	/* alive list, all locks (granted, blocked, listening) are on it */
	struct list_head	ln_alive_list;
	/* blocked list */
	struct list_head	ln_blocked_list;
	/* granted list */
	struct list_head	ln_granted_list;
	void			*ln_ev_target;
};

struct htree_lock {
	struct task_struct	*lk_task;
	struct htree_lock_head	*lk_head;
	void			*lk_private;
	unsigned		lk_depth;
	htree_lock_mode_t	lk_mode;
	struct list_head	lk_blocked_list;
	struct htree_lock_node	lk_nodes[0];
};

/* create a lock head, which stands for a resource */
struct htree_lock_head *htree_lock_head_alloc(unsigned depth,
					      unsigned hbits, unsigned priv);
/* free a lock head */
void htree_lock_head_free(struct htree_lock_head *lhead);
/* register event callback for child lock at level @depth */
void htree_lock_event_attach(struct htree_lock_head *lhead, unsigned depth,
			     unsigned events, htree_event_cb_t callback);
/* create a lock handle, which stands for a thread */
struct htree_lock *htree_lock_alloc(unsigned depth, unsigned pbytes);
/* free a lock handle */
void htree_lock_free(struct htree_lock *lck);
/* lock htree, when @wait is true, 0 is returned if the lock can't
 * be granted immediately */
int htree_lock_try(struct htree_lock *lck, struct htree_lock_head *lhead,
		   htree_lock_mode_t mode, int wait);
/* unlock htree */
void htree_unlock(struct htree_lock *lck);
/* unlock and relock htree with @new_mode */
int htree_change_lock_try(struct htree_lock *lck,
			  htree_lock_mode_t new_mode, int wait);
void htree_change_mode(struct htree_lock *lck, htree_lock_mode_t mode);
/* require child lock (key) of htree at level @dep, @event will be sent to all
 * listeners on this @key while lock being granted */
int htree_node_lock_try(struct htree_lock *lck, htree_lock_mode_t mode,
			u32 key, unsigned dep, int wait, void *event);
/* release child lock at level @dep, this lock will listen on it's key
 * if @event isn't NULL, event_cb will be called against @lck while granting
 * any other lock at level @dep with the same key */
void htree_node_unlock(struct htree_lock *lck, unsigned dep, void *event);
/* stop listening on child lock at level @dep */
void htree_node_stop_listen(struct htree_lock *lck, unsigned dep);
/* for debug */
void htree_lock_stat_print(int depth);
void htree_lock_stat_reset(void);

#define htree_lock(lck, lh, mode)	htree_lock_try(lck, lh, mode, 1)
#define htree_change_lock(lck, mode)	htree_change_lock_try(lck, mode, 1)

#define htree_lock_mode(lck)		((lck)->lk_mode)

#define htree_node_lock(lck, mode, key, dep)	\
	htree_node_lock_try(lck, mode, key, dep, 1, NULL)
/* this is only safe in thread context of lock owner */
#define htree_node_is_granted(lck, dep)		\
	((lck)->lk_nodes[dep].ln_mode != HTREE_LOCK_INVAL && \
	 (lck)->lk_nodes[dep].ln_mode != HTREE_LOCK_NL)
/* this is only safe in thread context of lock owner */
#define htree_node_is_listening(lck, dep)	\
	((lck)->lk_nodes[dep].ln_mode == HTREE_LOCK_NL)

#endif
