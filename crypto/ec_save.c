#include "hblk_crypto.h"

/**
 * ec_save - saves an existing EC key pair on the disk
 *
 * @key: points to the EC key pair to be saved on disk
 * @folder: the path to the folder in which to save the keys
 *
 * Return: 1 or 0 upon success or failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	char path[PATH_MAX];
	FILE *file;
	struct stat status;

	if (!key || !folder)
		return (0);

	/* Create the folder if it doesn't exist */
	if (stat(folder, &status) == -1)
		mkdir(folder, 0700);

	/* Save the private key */
	sprintf(path, "%s/%s", folder, PRI_FILENAME);

	file = fopen(path, "w");
	if (!file)
		return (0);

	if (!PEM_write_ECPrivateKey(file, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(file);
		return (0);
	}
	fclose(file);

	/* Save the public key */
	sprintf(path, "%s/%s", folder, PUB_FILENAME);

	file = fopen(path, "w");
	if (!file)
		return (0);

	if (!PEM_write_EC_PUBKEY(file, key))
	{
		fclose(file);
		return (0);
	}
	fclose(file);

	return (1);
}
