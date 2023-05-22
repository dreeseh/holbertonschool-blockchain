#include "hblk_crypto.h"

EC_KEY *ec_create(void)
{
	EC_KEY *key = EC_KEY_new();
	EC_GROUP *group = EC_GROUP_new_by_curve_name(EC_CURVE);

	if (key == NULL)
	{
		fprintf(stderr, "EC_KEY_new() failed\n");
		return (NULL);
	}

	if (group == NULL)
	{
		fprintf(stderr, "EC_GROUP_new_by_curve_name() failed\n");
		EC_KEY_free(key);
		return (NULL);
	}

	if (EC_KEY_set_group(key, group) != 1)
	{
		fprintf(stderr, "EC_KEY_set_group() failed\n");
		EC_GROUP_free(group);
		EC_KEY_free(key);
		return (NULL);
	}

	if (EC_KEY_generate_key(key) != 1)
	{
		fprintf(stderr, "EC_KEY_generate_key() failed\n");
		EC_KEY_free(key);
		return (NULL);
	}

	EC_GROUP_free(group);

	return (key);
}
