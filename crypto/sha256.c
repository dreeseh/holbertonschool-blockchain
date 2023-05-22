#include "hblk_crypto.h"

/**
 * sha256 - computes the hash of a sequence of bytes
 *
 * @s: the sequence of bytes to be hashed
 * @len: the number of bytes to hash in s
 * @digest: stores the resulting hash
 *
 * Return: a pointer to digest or NULL
 */
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX sha256_ctx;

	if (digest == NULL)
		return (NULL);

	if (!SHA256_Init(&sha256_ctx))
		return (NULL);

	if (!SHA256_Update(&sha256_ctx, s, len))
		return (NULL);

	if (!SHA256_Final(digest, &sha256_ctx))
		return (NULL);

	return (digest);
}
