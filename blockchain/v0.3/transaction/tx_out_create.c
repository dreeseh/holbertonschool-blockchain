#include "transaction.h"

/**
 * tx_out_create - allocates and initializes a transaction output structure
 *
 * @amount: the amount of the transaction
 * @pub: the public key of the transaction receiver
 *
 * Return: a pointer to the created transaction output upon success,
 *	   or NULL upon failure
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *tx_output;

	tx_output = malloc(sizeof(tx_out_t));
	if (!tx_output)
		return (NULL);

	tx_output->amount = amount;
	memcpy(tx_output->pub, pub, EC_PUB_LEN);
	sha256((int8_t const *)tx_output, EC_PUB_LEN + 4, tx_output->hash);

	return (tx_output);
}
