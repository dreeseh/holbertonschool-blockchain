#include "transaction.h"

/**
* match_inputs - checks if unspent token == input token
* @u_tx_out: unspent out transaction
* @tx_in: transaction input
*
* Return: 1 on match, else 0
*/
int match_inputs(unspent_tx_out_t *u_tx_out, tx_in_t *tx_in)
{
	if (memcmp(u_tx_out->out.hash, tx_in->tx_out_hash, 32))
		return (0);
	if (memcmp(u_tx_out->tx_id, tx_in->tx_id, 32))
		return (0);
	if (memcmp(u_tx_out->block_hash, tx_in->block_hash, 32))
		return (0);

	return (1);
}

/**
 * transaction_is_valid - checks whether a transaction is valid
 *
 * @transaction: points to the transaction to verify
 * @all_unspent: is the list of all unspent transaction outputs to date
 *
 * Return: return 1 if the transaction is valid, and 0 otherwise
 */
int transaction_is_valid(transaction_t const *transaction,
			 llist_t *all_unspent)
{
	tx_in_t *tx_in;
	unspent_tx_out_t *unspent_tx_out;
	int i, u, u_size;
	uint32_t a_in = 0, a_out = 0;
	EC_KEY *u_ec_key;
	uint8_t t_hash[SHA256_DIGEST_LENGTH];

	transaction_hash(transaction, t_hash);

	if (memcmp(transaction->id, t_hash, 32) != 0)
		return (0);
	u_size = llist_size(all_unspent);
	for (i = 0; i < llist_size(transaction->inputs); i++)
	{
		tx_in = llist_get_node_at(transaction->inputs, i);
		for (u = 0; u < u_size; u++)
		{
			unspent_tx_out = llist_get_node_at(all_unspent, u);
			if (match_inputs(unspent_tx_out, tx_in))
				break;
		}
		if (u == u_size)
			return (0);
		u_ec_key = ec_from_pub(unspent_tx_out->out.pub);
		u = ec_verify(u_ec_key, transaction->id, SHA256_DIGEST_LENGTH, &tx_in->sig);
		EC_KEY_free(u_ec_key);
		if (u == 0)
			return (0);
		a_in += unspent_tx_out->out.amount;
	}

	for (i = 0; i < llist_size(transaction->outputs); i++)
		a_out += ((tx_out_t *)llist_get_node_at(transaction->outputs, i))->amount;

	if (a_in != a_out)
		return (0);
	return (1);
}
