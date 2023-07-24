#include "transaction.h"

/**
 * coinbase_create - creates a coinbase transaction
 *
 * @receiver: contains the public key of the miner,
 *	      who will receive the coinbase coins
 * @block_index: the index of the Block the coinbase transaction will belong to
 *
 * Return: a pointer to the created transaction upon success,
 *	   or NULL upon failure
 */
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	transaction_t *transaction;
	tx_in_t *tx_in;
	tx_out_t *tx_out;
	uint8_t pubkey_out[EC_PUB_LEN];

	transaction = malloc(sizeof(transaction_t));
	if (transaction == NULL)
		return (NULL);
	tx_in = malloc(sizeof(tx_in_t));
	if (tx_in == NULL)
	{
		free(transaction);
		return (NULL);
	}

	memset(tx_in, 0, sizeof(*tx_in));
	memcpy(tx_in->tx_out_hash, &block_index, 4);

	ec_to_pub(receiver, pubkey_out);
	tx_out = tx_out_create(COINBASE_AMOUNT, pubkey_out);

	transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	transaction->outputs = llist_create(MT_SUPPORT_FALSE);

	llist_add_node(transaction->inputs, tx_in, ADD_NODE_REAR);
	llist_add_node(transaction->outputs, tx_out, ADD_NODE_REAR);

	transaction_hash(transaction, transaction->id);

	return (transaction);
}
