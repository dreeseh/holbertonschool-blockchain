#include "blockchain.h"

/**
 * hash_matches_difficulty - checks whether a given hash
 *			     matches a given difficulty
 *
 * @hash: the hash to check
 * @difficulty: the minimum difficulty the hash should match
 *
 * Return: 1 if the difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty)
{
	uint32_t leading_zeros, i, remaining_bits, mask;

	if (!hash)
		return (0);

	if (difficulty > SHA256_DIGEST_LENGTH * 8)
		return (0);

	/* calculate the number of required leading zeros */
	leading_zeros = difficulty / 8;

	/* check the bytes of the hash for the required leading zeros */
	for (i = 0; i < leading_zeros; i++)
	{
		if (hash[i] != 0)
			return (0);
	}

	/* Check the remaining bits of the difficulty */
	remaining_bits = difficulty % 8;
	mask = 255 << (8 - remaining_bits);

	if (hash[leading_zeros] & mask)
		return (0);

	return (1);
}
