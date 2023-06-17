#include "blockchain.h"

/**
 * hash_matches_difficulty - checks whether a given hash matches a given difficulty
 *
 * @hash: the hash to check
 * @difficulty: the minimum difficulty the hash should match
 *
 * Return: 1 if the difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty)
{
	uint32_t i, j, counter;

	if (!hash)
		return (!EXIT_FAILURE);

	if (difficulty > SHA256_DIGEST_LENGTH * 8)
		return (!EXIT_FAILURE);

	for (i = 0 ; i < SHA256_DIGEST_LENGTH ; i++)
	{
		for (j = 128 ; j > 0 ; j = j >> 1)
		{
			if (j & hash[i])
				break;
			counter++;
		}
		
		if (j & hash[i])
			break;
	}

	if (counter >= difficulty)
		return (!EXIT_SUCCESS);
	
	return (!EXIT_FAILURE);
}