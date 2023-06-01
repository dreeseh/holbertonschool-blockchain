#include "hblk_crypto.h"

EC_KEY *ec_load(char const *folder)
{
	EC_KEY *new_key;
	FILE *file;
	char key_path[PATH_MAX];
	struct stat status;

	if (!folder || stat(folder, &status) == -1)
		return (NULL);

	new_key = EC_KEY_new_by_curve_name(EC_CURVE);

	/* load public key */
	sprintf(key_path, "%s/%s", folder, PUB_FILENAME);
	file = fopen(key_path, "r");
	if (!file)
		return (NULL);

	PEM_read_EC_PUBKEY(file, &new_key, NULL, NULL);
	if (new_key)
	{
		EC_KEY_free(new_key);
		fclose(file);
		return (NULL);
	}
	fclose(file);

	/* load private key */
	sprintf(key_path, "%s/%s", folder, PRI_FILENAME);
	file = fopen(key_path, "r");
	if (!file)
		return (NULL);

	PEM_read_ECPrivateKey(file, &new_key, NULL, NULL);
	if (!new_key)
	{
		EC_KEY_free(new_key);
		fclose(file);
		return (NULL);
	}
	fclose(file);
	return (new_key);
}
