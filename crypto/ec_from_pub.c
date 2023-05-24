#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	EC_POINT *point;
	const EC_GROUP *group;

	/* generates a new key based upon the given curve */
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key || !pub)
		return (NULL);

	/* set group struct */
	group = EC_KEY_get0_group(key);

	/* Set the public key */
	point = EC_POINT_new(group);
	if (!point)
	{
		/* Failed to create EC_POINT structure */
		EC_KEY_free(key);
		return (NULL);
	}

	/* ec_point_oct2point converts the pub key */
	/* octect string to a usable EC_POINT */
	if (!EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL))
	{
		/* Failed to set the public key */
		EC_KEY_free(key);
		EC_POINT_free(point);
		return (NULL);
	}

	if (!EC_KEY_set_public_key(key, point))
	{
		/* Failed to set the public key in EC_KEY structure */
		EC_KEY_free(key);
		EC_POINT_free(point);
		return (NULL);
	}
	EC_POINT_free(point);
	return (key);
}
