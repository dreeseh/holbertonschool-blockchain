#include "transaction.h"

/**
 * init_transaction_t - initializes the transaction_t struct
 *
 * Return: a pointer to initialized transaction_t, or null upon failure
 */
transaction_t *init_transaction_t(void)
{
	transaction_t *transaction;

	transaction = calloc(1, sizeof(transaction_t));
	if (transaction == NULL)
		return (NULL);

	transaction->inputs = NULL;
	transaction->outputs = NULL;

	transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	if (transaction->inputs == NULL)
	{
		llist_destroy(transaction->inputs, 0, NULL);
		free(transaction);
		return (NULL);
	}

	transaction->outputs = llist_create(MT_SUPPORT_FALSE);
	if (transaction->outputs == NULL)
	{
		llist_destroy(transaction->outputs, 0, NULL);
		free(transaction);
		return (NULL);
	}

	return (transaction);
}

/**
 * sel_tx_inputs - determines which inputs to use for transaction
 *
 * @inputs: input llist to which nodes are added
 * @all_unspent: is the list of all the unspent outputs to date
 * @amount: is the amount to send
 * @sender_pub_key: the public key of the sender
 * Return: the difference in the token amounts
 */
uint32_t sel_tx_inputs(llist_t *inputs,
		       llist_t *all_unspent,
		       uint32_t amount,
		       uint8_t sender_pub_key[EC_PUB_LEN])
{
	unspent_tx_out_t *unspent_out;
	tx_in_t *input_transaction;
	int i;
	uint32_t difference = 0;

	for (i = 0 ; i < llist_size(all_unspent) ; i++)
	{
		unspent_out = llist_get_node_at(all_unspent, i);
		if (memcmp(unspent_out->out.pub, sender_pub_key, EC_PUB_LEN))
		{
			input_transaction = tx_in_create(unspent_out);
			llist_add_node(inputs, input_transaction, ADD_NODE_REAR);
			difference += unspent_out->out.amount;

			if (difference >= amount)
				break;
		}
	}
	return (difference);
}

/**
* t_cleanup - deletes a transaction_t
* @transaction: transacton to be deleted
* Return: always NULL
*/
transaction_t *t_cleanup(transaction_t *transaction)
{
	if (transaction->inputs)
		llist_destroy(transaction->inputs, 0, NULL);
	if (transaction->outputs)
		llist_destroy(transaction->outputs, 0, NULL);

	free(transaction);

	return (NULL);
}

/**
 * transaction_create - a function that creates a transaction
 *
 * @sender: contains the private key of the transaction sender
 * @receiver: contains the public key of the transaction receiver
 * @amount: is the amount to send
 * @all_unspent: the list of all the unspent outputs to date
 *
 * Return: a pointer to the created transaction upon success,
 *	   or NULL upon failure
 */
transaction_t *transaction_create(EC_KEY const *sender,
				  EC_KEY const *receiver,
				  uint32_t amount,
				  llist_t *all_unspent)
{
	transaction_t *transaction = NULL;
	uint8_t key_in[EC_PUB_LEN], key_out[EC_PUB_LEN];
	tx_in_t *tx_in;
	tx_out_t *tx_out;
	int i;
	uint32_t diff = 0;

	ec_to_pub(sender, key_in);
	ec_to_pub(receiver, key_out);
	transaction = init_transaction_t();
	if (transaction == NULL)
		return (NULL);

	diff = sel_tx_inputs(transaction->inputs, all_unspent, amount, key_in);
	if (diff < amount)
		return (t_cleanup(transaction));

	tx_out = tx_out_create(amount, key_out);
	llist_add_node(transaction->outputs, tx_out, ADD_NODE_REAR);
	if (diff > amount)
	{
		tx_out = tx_out_create(diff - amount, key_in);
		llist_add_node(transaction->outputs, tx_out, ADD_NODE_REAR);
	}
	transaction_hash(transaction, transaction->id);

	for (i = 0; i < llist_size(transaction->inputs); i++)
	{
		tx_in = llist_get_node_at(transaction->inputs, i);
		if (tx_in_sign(tx_in, transaction->id, sender, all_unspent) == 0)
			return (t_cleanup(transaction));
	}
	return (transaction);
}
