#include "blockchain.h"

/**
 * block_create - creates a Block structure and initializes it
 *
 * @prev: a pointer to the previous Block in the Blockchain
 * @data: points to a memory area to duplicate in the Block’s data
 * @data_len: stores the number of bytes to duplicate in data.
 *	      If data_len is bigger than BLOCKCHAIN_DATA_MAX,
 *	      then only BLOCKCHAIN_DATA_MAX bytes must be duplicated
 *
 * Return: a pointer to the allocated Block
 */
block_t *block_create(block_t const *prev, int8_t
			const *data, uint32_t data_len)
{
	block_t *new_block;

	new_block = calloc(1, sizeof(block_t));
	if (!new_block)
		return (NULL);

	new_block->info.index = prev->info.index + 1;
	new_block->info.timestamp = time(NULL);
	memcpy(new_block->info.prev_hash, prev->hash, SHA224_DIGEST_LENGTH);
	memset(new_block->hash, 0, SHA256_DIGEST_LENGTH);

	memcpy(new_block->data.buffer, data, data_len);
	new_block->data.len = data_len;

	return (new_block);
}
