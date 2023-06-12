#include "blockchain.h"

/**
 * block_hash - computes the hash of a Block
 *
 * @block: points to the Block to be hashed
 * @hash_buf: stores the resulting hash
 *
 * Return: a pointer to hash_buf
 */
uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	sha256((int8_t const *)block,
		sizeof(block_info_t) + block->data.len, 
		hash_buf);

	return (hash_buf);
}
