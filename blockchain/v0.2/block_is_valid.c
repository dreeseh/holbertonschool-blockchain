#include "blockchain.h"

/**
 * block_is_valid - verifies that a Block is valid
 *
 * @block: points to the Block to check
 * @prev_block: points to the previous Block in the Blockchain
 *		NULL if block is the first Block of the chain
 *
 * Return: 0 is valid, 1 is NOT valid
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};
	block_t const _genesis = GENESIS_BLOCK;

	/* block cant be NULL & prev block can only be NULL if index = 0 */
	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	/* if index = 0, it should match genesis block */
	if (block->info.index == 0)
		return (memcmp(block, &_genesis, sizeof(_genesis)));
	/* block's index must incriment by 1 */
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	/* The computed hash of the previous block must match the one it stores */
	if (!block_hash(prev_block, hash_buf) ||
		memcmp(hash_buf, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	/* computed hash of previous block must match the reference stored in block */
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	/* The computed hash of the Block must match the one it stores */
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	/* The Block data length must not exceed BLOCKCHAIN_DATA_MAX */
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	return (0);
}
