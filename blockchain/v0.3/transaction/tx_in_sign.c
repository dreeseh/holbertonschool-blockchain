#include "transaction.h"

/**
 * tx_in_sign - signs a transaction input, given the transaction id it is from
 *
 * @in: points to the transaction input structure to sign
 * @tx_id: contains the ID (hash) of the transaction
 *	   the transaction input to sign is stored in
 * @sender: contains the private key of the receiver of
 *	    the coins contained in the transaction output
 *	    referenced by the transaction input
 * @all_unspent: the list of all unspent transaction outputs to date
 *
 * Return: a pointer to the resulting signature structure upon success,
 *	   or NULL upon failure
 */
sig_t *tx_in_sign(tx_in_t *in,
		  uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		  EC_KEY const *sender, llist_t *all_unspent)
{
	uint8_t sender_pub[EC_PUB_LEN];
	ssize_t i;
	unspent_tx_out_t *utxo;

	if (in == NULL || tx_id == NULL || sender == NULL || all_unspent == NULL)
		return (NULL);

	/* verify the pub key hash from sender matches the transaction output hash */
	for  (i = 0 ; i < llist_size(all_unspent) ; i++)
	{
		utxo = llist_get_node_at(all_unspent, i);
		if (!memcmp(in->tx_out_hash, utxo->out.hash, 32))
			break;

	}

	/* verify the public key derived from the private key in sender matches the */
	/* public key stored in the transaction output referenced by the */
	/* transaction input to be signed */
	if (!ec_to_pub(sender, sender_pub))
		return (NULL);

	if (memcmp(sender_pub, utxo->out.pub, EC_PUB_LEN))
		return (NULL);

	/* Sign the transaction ID using the sender's private key */
	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig))
		return (NULL);

	/* return a pointer to the resulting signature structure */
	return (&in->sig);
}
