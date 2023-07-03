#include "transaction.h"

/**
 * tx_in_create - allocates and initializes a transaction input structure
 *
 * @unspent: points to the unspent transaction output
 *	     to be converted to a transaction input
 *
 * Return: a pointer to the created transaction input upon success,
 *	   or NULL upon failure
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *output;

	output = malloc(sizeof(tx_in_t));
	if (output == NULL)
		return (NULL);

	memcpy(output->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(output->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(output->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);
	memset(&output->sig, 0, sizeof(output->sig));

	return (output);
}
