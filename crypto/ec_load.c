#include "hblk_crypto.h"

EC_KEY *ec_load(char const *folder)
{
	EC_KEY *private_key, *public_key;
	FILE *file;
	char key_path[PATH_MAX];

	if (!folder)
		return (NULL);

	/* load private key */
	sprintf(key_path, "%s/%s", folder, PRI_FILENAME);
	file = fopen(key_path, "r");
	if (!file)
		return (NULL);

	private_key = PEM_read_ECPrivateKey(file, NULL, NULL, NULL);
	if (!private_key)
	{
		fclose(file);
		return (NULL);
	}
	fclose(file);

	/* load public key */
	sprintf(key_path, "%s/%s", folder, PUB_FILENAME);
	file = fopen(key_path, "r");
	if (!file)
		return (NULL);

	public_key = PEM_read_EC_PUBKEY(file, NULL, NULL, NULL);
	if (!public_key)
	{
		fclose(file);
		return (NULL);
	}
	fclose(file);

	/* set public key 
	if (EC_KEY_set_public_key(private_key, EC_KEY_get0_public_key(public_key)) == 0)
	{
		EC_KEY_free(private_key);
		EC_KEY_free(public_key);
		return (NULL);
	}
	*/
	EC_KEY_free(public_key);
	return (private_key);
}