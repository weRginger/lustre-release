/* GPL HEADER START
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
 * version 2 along with this program; If not, see http://www.gnu.org/licenses
 *
 * Please  visit http://www.xyratex.com/contact if you need additional
 * information or have any questions.
 *
 * GPL HEADER END
 */

/*
 * Copyright 2012 Xyratex Technology Limited
 *
 * Copyright (c) 2012, 2014, Intel Corporation.
 */

#include <linux/crypto.h>
#include <linux/scatterlist.h>
#include <libcfs/libcfs.h>
#include <libcfs/libcfs_crypto.h>
#include <libcfs/linux/linux-crypto.h>
/**
 *  Array of hash algorithm speed in MByte per second
 */
static int cfs_crypto_hash_speeds[CFS_HASH_ALG_MAX];

/**
 * Initialize the state descriptor for the specified hash algorithm.
 *
 * An internal routine to allocate the hash-specific state in \a hdesc for
 * use with cfs_crypto_hash_digest() to compute the hash of a single message,
 * though possibly in multiple chunks.  The descriptor internal state should
 * be freed with cfs_crypto_hash_final().
 *
 * \param[in]  hash_alg	hash algorithm id (CFS_HASH_ALG_*)
 * \param[out] type	pointer to the hash description in hash_types[] array
 * \param[in,out] hdesc	hash state descriptor to be initialized
 * \param[in]  key	initial hash value/state, NULL to use default value
 * \param[in]  key_len	length of \a key
 *
 * \retval		0 on success
 * \retval		negative errno on failure
 */
static int cfs_crypto_hash_alloc(enum cfs_crypto_hash_alg hash_alg,
				 const struct cfs_crypto_hash_type **type,
				 struct hash_desc *hdesc, unsigned char *key,
				 unsigned int key_len)
{
	int err = 0;

	*type = cfs_crypto_hash_type(hash_alg);

	if (*type == NULL) {
		CWARN("Unsupported hash algorithm id = %d, max id is %d\n",
		      hash_alg, CFS_HASH_ALG_MAX);
		return -EINVAL;
	}
	hdesc->tfm = crypto_alloc_hash((*type)->cht_name, 0, 0);

	if (hdesc->tfm == NULL)
		return -EINVAL;

	if (IS_ERR(hdesc->tfm)) {
		CDEBUG(D_INFO, "Failed to alloc crypto hash %s\n",
		       (*type)->cht_name);
		return PTR_ERR(hdesc->tfm);
	}

	hdesc->flags = 0;

	if (key != NULL)
		err = crypto_hash_setkey(hdesc->tfm, key, key_len);
	else if ((*type)->cht_key != 0)
		err = crypto_hash_setkey(hdesc->tfm,
					 (unsigned char *)&((*type)->cht_key),
					 (*type)->cht_size);

	if (err != 0) {
		crypto_free_hash(hdesc->tfm);
		return err;
	}

	CDEBUG(D_INFO, "Using crypto hash: %s (%s) speed %d MB/s\n",
	       (crypto_hash_tfm(hdesc->tfm))->__crt_alg->cra_name,
	       (crypto_hash_tfm(hdesc->tfm))->__crt_alg->cra_driver_name,
	       cfs_crypto_hash_speeds[hash_alg]);

	return crypto_hash_init(hdesc);
}

/**
 * Calculate hash digest for the passed buffer.
 *
 * This should be used when computing the hash on a single contiguous buffer.
 * It combines the hash initialization, computation, and cleanup.
 *
 * \param[in] hash_alg	id of hash algorithm (CFS_HASH_ALG_*)
 * \param[in] buf	data buffer on which to compute hash
 * \param[in] buf_len	length of \a buf in bytes
 * \param[in] key	initial value/state for algorithm, if \a key = NULL
 *			use default initial value
 * \param[in] key_len	length of \a key in bytes
 * \param[out] hash	pointer to computed hash value, if \a hash = NULL then
 *			\a hash_len is to digest size in bytes, retval -ENOSPC
 * \param[in,out] hash_len size of \a hash buffer
 *
 * \retval -EINVAL       \a buf, \a buf_len, \a hash_len, \a alg_id invalid
 * \retval -ENOENT       \a hash_alg is unsupported
 * \retval -ENOSPC       \a hash is NULL, or \a hash_len less than digest size
 * \retval		0 for success
 * \retval		negative errno for other errors from lower layers.
 */
int cfs_crypto_hash_digest(enum cfs_crypto_hash_alg hash_alg,
			   const void *buf, unsigned int buf_len,
			   unsigned char *key, unsigned int key_len,
			   unsigned char *hash, unsigned int *hash_len)
{
	struct scatterlist	sl;
	struct hash_desc	hdesc;
	int			err;
	const struct cfs_crypto_hash_type	*type;

	if (buf == NULL || buf_len == 0 || hash_len == NULL)
		return -EINVAL;

	err = cfs_crypto_hash_alloc(hash_alg, &type, &hdesc, key, key_len);
	if (err != 0)
		return err;

	if (hash == NULL || *hash_len < type->cht_size) {
		*hash_len = type->cht_size;
		crypto_free_hash(hdesc.tfm);
		return -ENOSPC;
	}
	sg_init_one(&sl, (void *)buf, buf_len);

	hdesc.flags = 0;
	err = crypto_hash_digest(&hdesc, &sl, sl.length, hash);
	crypto_free_hash(hdesc.tfm);

	return err;
}
EXPORT_SYMBOL(cfs_crypto_hash_digest);

/**
 * Allocate and initialize desriptor for hash algorithm.
 *
 * This should be used to initialize a hash descriptor for multiple calls
 * to a single hash function when computing the hash across multiple
 * separate buffers or pages using cfs_crypto_hash_update{,_page}().
 *
 * The hash descriptor should be freed with cfs_crypto_hash_final().
 *
 * \param[in] hash_alg	algorithm id (CFS_HASH_ALG_*)
 * \param[in] key	initial value/state for algorithm, if \a key = NULL
 *			use default initial value
 * \param[in] key_len	length of \a key in bytes
 *
 * \retval		pointer to descriptor of hash instance
 * \retval		ERR_PTR(errno) in case of error
 */
struct cfs_crypto_hash_desc *
	cfs_crypto_hash_init(enum cfs_crypto_hash_alg hash_alg,
			     unsigned char *key, unsigned int key_len)
{

	struct  hash_desc			*hdesc;
	int					err;
	const struct cfs_crypto_hash_type       *type;

	hdesc = kmalloc(sizeof(*hdesc), 0);
	if (hdesc == NULL)
		return ERR_PTR(-ENOMEM);

	err = cfs_crypto_hash_alloc(hash_alg, &type, hdesc, key, key_len);

	if (err) {
		kfree(hdesc);
		hdesc = ERR_PTR(err);
	}
	return (struct cfs_crypto_hash_desc *)hdesc;
}
EXPORT_SYMBOL(cfs_crypto_hash_init);

/**
 * Update hash digest computed on data within the given \a page
 *
 * \param[in] hdesc	hash state descriptor
 * \param[in] page	data page on which to compute the hash
 * \param[in] offset	offset within \a page at which to start hash
 * \param[in] len	length of data on which to compute hash
 *
 * \retval		0 for success
 * \retval		negative errno on failure
 */
int cfs_crypto_hash_update_page(struct cfs_crypto_hash_desc *hdesc,
				struct page *page, unsigned int offset,
				unsigned int len)
{
	struct scatterlist sl;

	sg_init_table(&sl, 1);
	sg_set_page(&sl, page, len, offset & ~PAGE_MASK);

	return crypto_hash_update((struct hash_desc *)hdesc, &sl, sl.length);
}
EXPORT_SYMBOL(cfs_crypto_hash_update_page);

/**
 * Update hash digest computed on the specified data
 *
 * \param[in] hdesc	hash state descriptor
 * \param[in] buf	data buffer on which to compute the hash
 * \param[in] buf_len	length of \buf on which to compute hash
 *
 * \retval		0 for success
 * \retval		negative errno on failure
 */
int cfs_crypto_hash_update(struct cfs_crypto_hash_desc *hdesc,
			   const void *buf, unsigned int buf_len)
{
	struct scatterlist sl;

	sg_init_one(&sl, (void *)buf, buf_len);

	return crypto_hash_update((struct hash_desc *)hdesc, &sl, sl.length);
}
EXPORT_SYMBOL(cfs_crypto_hash_update);

/**
 * Finish hash calculation, copy hash digest to buffer, clean up hash descriptor
 *
 * \param[in]	hdesc		hash descriptor
 * \param[out]	hash		pointer to hash buffer to store hash digest
 * \param[in,out] hash_len	pointer to hash buffer size, if \a hash == NULL
 *				or hash_len == NULL only free \a hdesc instead
 *				of computing the hash
 *
 * \retval		0 for success
 * \retval		-EOVERFLOW if hash_len is too small for the hash digest
 * \retval		negative errno for other errors from lower layers
 */
int cfs_crypto_hash_final(struct cfs_crypto_hash_desc *hdesc,
			  unsigned char *hash, unsigned int *hash_len)
{
	int     size = crypto_hash_digestsize(((struct hash_desc *)hdesc)->tfm);
	int     err;

	if (hash == NULL || hash_len == NULL) {
		err = 0;
		goto free;
	}
	if (*hash_len < size) {
		err = -EOVERFLOW;
		goto free;
	}

	err = crypto_hash_final((struct hash_desc *)hdesc, hash);
	if (err == 0)
		*hash_len = size;
free:
	crypto_free_hash(((struct hash_desc *)hdesc)->tfm);
	kfree(hdesc);

	return err;
}
EXPORT_SYMBOL(cfs_crypto_hash_final);

/**
 * Compute the speed of specified hash function
 *
 * Run a speed test on the given hash algorithm on buffer of the given size.
 * The speed is stored internally in the cfs_crypto_hash_speeds[] array, and
 * is available through the cfs_crypto_hash_speed() function.
 *
 * \param[in] hash_alg	hash algorithm id (CFS_HASH_ALG_*)
 * \param[in] buf	data buffer on which to compute the hash
 * \param[in] buf_len	length of \buf on which to compute hash
 */
static void cfs_crypto_performance_test(enum cfs_crypto_hash_alg hash_alg)
{
	int			buf_len = max(PAGE_SIZE, 1048576UL);
	void			*buf;
	unsigned long		start, end;
	int			bcount, err = 0;
	struct page		*page;
	unsigned char		hash[CFS_CRYPTO_HASH_DIGESTSIZE_MAX];
	unsigned int		hash_len = sizeof(hash);

	page = alloc_page(GFP_KERNEL);
	if (page == NULL) {
		err = -ENOMEM;
		goto out_err;
	}

	buf = kmap(page);
	memset(buf, 0xAD, PAGE_SIZE);
	kunmap(page);

	for (start = jiffies, end = start + msecs_to_jiffies(MSEC_PER_SEC),
	     bcount = 0;
	     time_before(jiffies, end) && err == 0; bcount++) {
		struct cfs_crypto_hash_desc *hdesc;
		int i;

		hdesc = cfs_crypto_hash_init(hash_alg, NULL, 0);
		if (IS_ERR(hdesc)) {
			err = PTR_ERR(hdesc);
			break;
		}

		for (i = 0; i < buf_len / PAGE_SIZE; i++) {
			err = cfs_crypto_hash_update_page(hdesc, page, 0,
							  PAGE_SIZE);
			if (err != 0)
				break;
		}

		err = cfs_crypto_hash_final(hdesc, hash, &hash_len);
		if (err != 0)
			break;
	}
	end = jiffies;
	__free_page(page);
out_err:
	if (err != 0) {
		cfs_crypto_hash_speeds[hash_alg] = err;
		CDEBUG(D_INFO, "Crypto hash algorithm %s test error: rc = %d\n",
		       cfs_crypto_hash_name(hash_alg), err);
	} else {
		unsigned long   tmp;

		tmp = ((bcount * buf_len / jiffies_to_msecs(end - start)) *
		       1000) / (1024 * 1024);
		cfs_crypto_hash_speeds[hash_alg] = (int)tmp;
		CDEBUG(D_CONFIG, "Crypto hash algorithm %s speed = %d MB/s\n",
		       cfs_crypto_hash_name(hash_alg),
		       cfs_crypto_hash_speeds[hash_alg]);
	}
}

/**
 * hash speed in Mbytes per second for valid hash algorithm
 *
 * Return the performance of the specified \a hash_alg that was previously
 * computed using cfs_crypto_performance_test().
 *
 * \param[in] hash_alg	hash algorithm id (CFS_HASH_ALG_*)
 *
 * \retval		positive speed of the hash function in MB/s
 * \retval		-ENOENT if \a hash_alg is unsupported
 * \retval		negative errno if \a hash_alg speed is unavailable
 */
int cfs_crypto_hash_speed(enum cfs_crypto_hash_alg hash_alg)
{
	if (hash_alg < CFS_HASH_ALG_MAX)
		return cfs_crypto_hash_speeds[hash_alg];

	return -ENOENT;
}
EXPORT_SYMBOL(cfs_crypto_hash_speed);

/**
 * Run the performance test for all hash algorithms.
 *
 * Run the cfs_crypto_performance_test() benchmark for all of the available
 * hash functions using a 1MB buffer size.  This is a reasonable buffer size
 * for Lustre RPCs, even if the actual RPC size is larger or smaller.
 *
 * Since the setup cost and computation speed of various hash algorithms is
 * a function of the buffer size (and possibly internal contention of offload
 * engines), this speed only represents an estimate of the actual speed under
 * actual usage, but is reasonable for comparing available algorithms.
 *
 * The actual speeds are available via cfs_crypto_hash_speed() for later
 * comparison.
 *
 * \retval		0 on success
 * \retval		-ENOMEM if no memory is available for test buffer
 */
static int cfs_crypto_test_hashes(void)
{
	enum cfs_crypto_hash_alg hash_alg;

	for (hash_alg = 0; hash_alg < CFS_HASH_ALG_MAX; hash_alg++)
		cfs_crypto_performance_test(hash_alg);

	return 0;
}

static int adler32;

#ifdef HAVE_CRC32
static int crc32;
#endif
#ifdef HAVE_PCLMULQDQ
#ifdef NEED_CRC32_ACCEL
static int crc32_pclmul;
#endif
#ifdef NEED_CRC32C_ACCEL
static int crc32c_pclmul;
#endif
#endif /* HAVE_PCLMULQDQ */

/**
 * Register available hash functions
 *
 * \retval		0
 */
int cfs_crypto_register(void)
{
	request_module("crc32c");

	adler32 = cfs_crypto_adler32_register();

#ifdef HAVE_CRC32
	crc32 = cfs_crypto_crc32_register();
#endif
#ifdef HAVE_PCLMULQDQ
#ifdef NEED_CRC32_ACCEL
	crc32_pclmul = cfs_crypto_crc32_pclmul_register();
#endif
#ifdef NEED_CRC32C_ACCEL
	crc32c_pclmul = cfs_crypto_crc32c_pclmul_register();
#endif
#endif /* HAVE_PCLMULQDQ */

	/* check all algorithms and do performance test */
	cfs_crypto_test_hashes();

	return 0;
}

/**
 * Unregister previously registered hash functions
 */
void cfs_crypto_unregister(void)
{
	if (adler32 == 0)
		cfs_crypto_adler32_unregister();

#ifdef HAVE_CRC32
	if (crc32 == 0)
		cfs_crypto_crc32_unregister();
#endif
#ifdef HAVE_PCLMULQDQ
#ifdef NEED_CRC32_ACCEL
	if (crc32_pclmul == 0)
		cfs_crypto_crc32_pclmul_unregister();
#endif
#ifdef NEED_CRC32C_ACCEL
	if (crc32c_pclmul == 0)
		cfs_crypto_crc32c_pclmul_unregister();
#endif
#endif /* HAVE_PCLMULQDQ */
}
