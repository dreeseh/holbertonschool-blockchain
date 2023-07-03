#include "blockchain.h"

/**
 * block_mine - mines a Block in order to insert it in the Blockchain
 *
 * @block: points to the block to be mined
 *
 * Return: is void
 */
void block_mine(block_t *block)
{
	uint32_t nonce = 0;
	uint8_t hash[SHA256_DIGEST_LENGTH];

	if (!block)
		return;
	/**
	 * We use a nonce value that starts from zero & continuously increments.
	 * Every time we increment, we recalculate the block's hash value until it
	 * finds a hash that matches the difficulty we're looking for.
	 *
	 * when the matching hash is found, we update the block's nonce & we copy
	 * the hash into the block's hash array.
	 */
	while (1)
	{
		/* start the block's nonce at zero & update as we go */
		block->info.nonce = nonce;

		/* recalculating the block's hash value */
		block_hash(block, hash);

		/* look for the matching difficulty */
		if (hash_matches_difficulty(hash, block->info.difficulty))
		{
			/* copy the hash into the block's hash array */
			memcpy(block->hash, hash, SHA256_DIGEST_LENGTH);
			break;
		}
		/* continuously incrementing nonce */
		nonce++;
	}
}
