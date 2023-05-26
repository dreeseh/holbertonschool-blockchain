#include "hblk_crypto.h"

/**
 * ec_verify - verifies the signature of a given set of bytes,
 * using a given EC_KEY public key
 *
 * @key: points to the EC_KEY structure containing the public key to be used
 * @msg: points to the msglen characters to verify the signature
 * @msglen: length of the message
 * @sig: points to the signature to be checked
 *
 * Return: 1 if the signature is valid, and 0 otherwise
 * if either key, msg or sig is NULL, the function must fail
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !sig)
		return (0);

	if (ECDSA_verify(0,
			 msg,
			 msglen,
			 sig->sig, sig->len,
			 (EC_KEY *)key) != 1)
		return (0);

	return (1);
}
