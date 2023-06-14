#include "blockchain.h"

blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fd;
	uint32_t i;
	block_t *hblk_block;
	block_header_t hblk_header;
	blockchain_t *hblk_blockchain;

	fd = fopen(path, "r");
	if (!fd)
		return (NULL);

	fread(&hblk_header, sizeof(hblk_header), 1, fd);
	if (!header_checker(&hblk_header))
		return (NULL);

	if (hblk_header.hblk_endian == 2)
		_swap_endian(&hblk_header.hblk_blocks,
		sizeof(hblk_header.hblk_blocks));

	if (hblk_header.hblk_blocks == 0)
	{
		fclose(fd);
		return (NULL);
	}

	hblk_blockchain = malloc(sizeof(blockchain_t));
	if (!hblk_blockchain)
		return (NULL);
	hblk_blockchain->chain = llist_create(MT_SUPPORT_FALSE);

	for (i = 0 ; i < hblk_header.hblk_blocks ; i++)
	{
		hblk_block = malloc(sizeof(block_t));
		if (!hblk_block)
			return (NULL);
		fread(hblk_block, 56, 1, fd);
		fread(&hblk_block->data.len, 4, 1, fd);
		if (hblk_header.hblk_endian == 2)
			block_swap(hblk_block);
		memset(hblk_block->data.buffer,  0, sizeof(hblk_block->data.buffer));
		fread(&hblk_block->data.buffer, hblk_block->data.len, 1, fd);
		fread(&hblk_block->hash, 32, 1, fd);

		llist_add_node(hblk_blockchain->chain, hblk_block, ADD_NODE_REAR);
	}
	fclose(fd);
	return (hblk_blockchain);
}

int header_checker(block_header_t *hblk_header)
{
	if (memcmp(hblk_header->hblk_magic, "HBLK", 4) != 0 ||
	    memcmp(hblk_header->hblk_version, "0.1", 3) != 0)
		return (0);

	return (1);
}

void block_swap(block_t *hblk_block)
{
	_swap_endian(&hblk_block->info.index, 4);
	_swap_endian(&hblk_block->info.difficulty, 4);
	_swap_endian(&hblk_block->info.timestamp, 8);
	_swap_endian(&hblk_block->info.nonce, 8);
	_swap_endian(&hblk_block->data.len, 4);
}
