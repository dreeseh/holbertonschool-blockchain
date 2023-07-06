#include "transaction.h"

/**
 * transaction_hash - computes the ID (hash) of a transaction
 *
 * @transaction: points to the transaction to compute the hash of
 * @hash_buf: a buffer in which to store the computed hash
 *
 * Return: a pointer to hash_buf
 */
uint8_t *transaction_hash(transaction_t const *transaction,
			  uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX my_sha256_ctx;
	uint8_t buffer[SHA256_DIGEST_LENGTH];
	size_t i;
	size_t length;

	if (transaction == NULL || hash_buf == NULL)
		return (NULL);

	/* Initialize SHA256 context */
	if (!SHA256_Init(&my_sha256_ctx))
		return (NULL);

	/* Hash inputs */
	length = llist_size(transaction->inputs);
	for (i = 0; i < length; ++i)
	{
		tx_in_t *input = llist_get_node_at(transaction->inputs, i);

		if (input == NULL)
		return (NULL);

	/* Hash block_hash */
	if (!SHA256_Update(&my_sha256_ctx,
			   input->block_hash,
			   sizeof(input->block_hash)))
		return (NULL);

	/* Hash tx_id */
	if (!SHA256_Update(&my_sha256_ctx,
			   input->tx_id,
			   sizeof(input->tx_id)))
		return (NULL);

	/* Hash tx_out_hash */
	if (!SHA256_Update(&my_sha256_ctx,
			   input->tx_out_hash,
			   sizeof(input->tx_out_hash)))
		return (NULL);
	}

	/* Hash outputs */
	length = llist_size(transaction->outputs);
	for (i = 0; i < length; ++i)
	{
		tx_out_t *output = llist_get_node_at(transaction->outputs, i);

		if (output == NULL)
			return (NULL);

		/* Hash output hash */
		if (!SHA256_Update(&my_sha256_ctx,
				   output->hash,
				   sizeof(output->hash)))
		return (NULL);
	}

	/* Finalize the hash */
	if (!SHA256_Final(buffer, &my_sha256_ctx))
		return (NULL);

	/* Copy the hash to the output buffer */
	memcpy(hash_buf, buffer, SHA256_DIGEST_LENGTH);

	return (hash_buf);
}
