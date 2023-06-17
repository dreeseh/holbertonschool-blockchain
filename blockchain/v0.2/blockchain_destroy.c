#include "blockchain.h"

/**
 * blockchain_destroy - deletes an existing Blockchain,
 *			along with all the Blocks it contains
 *
 * @blockchain: points to the Blockchain structure to delete
 *
 * Return: is void
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->chain, 1, (node_dtor_t)free);
	free(blockchain);
}
