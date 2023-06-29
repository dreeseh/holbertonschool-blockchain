#include "blockchain.h"

/**
 * blockchain_difficulty - computes the difficulty to assign
 *			   to a potential next Block in the Blockchain
 *
 * @blockchain: points to the Blockchain to analyze
 *
 * Return: the difficulty to be assigned to a
 *	   potential next Block in the Blockchain
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *current_block, *prev_and_adjusted;
	uint64_t expected_time, actual_time;
	uint32_t difficulty;

	if (!blockchain || !blockchain->chain)
		return (0);

	current_block = llist_get_tail(blockchain->chain);

	/* if block is GENISIS block, no need to change difficulty */
	if (current_block->info.index == 0)
		return (current_block->info.difficulty);

	/* if block is not a multiple of DIFFICULTY_ADJUSTMENT_INTERVAL, no change */
	if (current_block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL != 0)
		return (current_block->info.difficulty);

	/* Retrieve the last Block for which an adjustment was made */
	prev_and_adjusted = llist_get_node_at(blockchain->chain,
					      current_block->info.index - DIFFICULTY_ADJUSTMENT_INTERVAL + 1);

	/* Compute the expected elapsed time between the two Blocks */
	expected_time = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL;
	/* compute the actual elapsed time*/
	actual_time = current_block->info.timestamp -
		      prev_and_adjusted->info.timestamp;
	/* if our time is less than half the expected time */
	/* the difficulty is incremented by 1 */
	if (actual_time < expected_time / 2)
		difficulty = current_block->info.difficulty + 1;
	/* if our time is more than twice the expected time */
	/* the difficulty is decremented by 1 */
	else if (actual_time > expected_time * 2)
		difficulty = current_block->info.difficulty - 1;
	/* otherwise, our difficulty will stay the same */
	else
		/* The difficulty should not change otherwise */
		difficulty = current_block->info.difficulty;

	return (difficulty);
}
