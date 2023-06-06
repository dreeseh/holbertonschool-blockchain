#include "blockchain.h"

/**
 * blockchain_create - creates a Blockchain structure, and initializes it
 *
 * Return: pointer to the new blockchain or NULL upon failure
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *new_blockchain = NULL;
	block_t *new_block = NULL;

	new_blockchain = malloc(sizeof(blockchain_t));
	if (!new_blockchain)
		return (NULL);

	new_block = malloc(sizeof(block_t));
	if (!new_block)
	{
		free(new_blockchain);
		return (NULL);
	}

	new_blockchain->chain = llist_create(MT_SUPPORT_TRUE);
	if (!new_blockchain->chain)
	{
		free(new_blockchain->chain);
		free(new_blockchain);
		free(new_block);
		return (NULL);
	}

	new_block->info.index = 0;
	new_block->info.difficulty = 0;
	new_block->info.timestamp = GENESIS_TIMESTAMP;
	new_block->info.nonce = 0;
	memset(new_block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);

	memcpy(new_block->data.buffer, GENESIS_DATA, GENESIS_DATA_LEN);
	new_block->data.len = GENESIS_DATA_LEN;

	memcpy(new_block->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);

	if (llist_add_node(new_blockchain->chain, new_block, ADD_NODE_FRONT) != 0)
	{
		free(new_block);
		free(new_blockchain->chain);
		free(new_blockchain);
		return (NULL);
	}

	return (new_blockchain);
}
