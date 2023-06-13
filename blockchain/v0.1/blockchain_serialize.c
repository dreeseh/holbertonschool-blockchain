#include "blockchain.h"

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *fd;
	uint32_t i;
	block_t *new_block;
	block_header_t hblk_header;

	initialize_blk_header(&hblk_header);
	hblk_header.hblk_blocks = llist_size(blockchain->chain);

	fd = fopen(path, "wb");
	if (!fd)
		return (-1);

	fwrite(&hblk_header, 1, sizeof(hblk_header), fd);
	for (i = 0 ; i < hblk_header.hblk_blocks ; i++)
	{
		new_block = llist_get_node_at(blockchain->chain, i);
		fwrite(new_block, 1, 56, fd);
		fwrite(&new_block->data.len, 1, 4, fd);
		fwrite(&new_block->data.buffer, 1, new_block->data.len, fd);
		fwrite(&new_block->hash, 1, 32, fd);
	}
	fclose(fd);

	return (0);
}

void initialize_blk_header(block_header_t *hblk_header)
{
	hblk_header->hblk_magic[0] = 'H';
	hblk_header->hblk_magic[1] = 'B';
	hblk_header->hblk_magic[2] = 'L';
	hblk_header->hblk_magic[3] = 'K';
	hblk_header->hblk_version[0] = '0';
	hblk_header->hblk_version[1] = '.';
	hblk_header->hblk_version[2] = '1';
	hblk_header->hblk_endian = 1;
	hblk_header->hblk_blocks = 0;
}
