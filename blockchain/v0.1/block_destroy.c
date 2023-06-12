#include "blockchain.h"

/**
 * block_destroy - deletes an existing Block
 *
 * @block: points to the Block to delete
 *
 * Return: is void
 */
void block_destroy(block_t *block)
{
	if (!block)
		return;

	free(block);
}
