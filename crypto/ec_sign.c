#include "hblk_crypto.h"

/**
 * ec_sign - signs a given set of bytes, using a given EC_KEY private key
 *
 * @key: points to the EC_KEY structure containing the private key
 * @msg: points to the msglen characters to be signed
 * @msglen: length of the message
 * @sig: holds the address at which to store the signature
 *
 * Return: pointer to the signature buffer or NULL upon failure
 */
uint8_t *ec_sign(EC_KEY const *key,
		 uint8_t const *msg,
		 size_t msglen,
		 sig_t *sig)
{
	unsigned int siglen;

	if (key == NULL || msg == NULL || sig == NULL)
		return (NULL);

	if (ECDSA_sign(0, msg, (int)msglen, sig->sig, &siglen, (EC_KEY *)key) == 0)
		return (NULL);

	sig->len = (uint8_t)siglen;

	return (sig->sig);
}
