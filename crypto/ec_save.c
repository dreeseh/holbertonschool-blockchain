#include "hblk_crypto.h"

int ec_save(EC_KEY *key, char const *folder)
{
	char path[256];
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
