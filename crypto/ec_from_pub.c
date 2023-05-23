#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key = EC_KEY_new();
	EC_GROUP *group = EC_GROUP_new_by_curve_name(EC_CURVE);
	EC_POINT *point = EC_POINT_new(group);
	BIGNUM *bn_pub_x = BN_bin2bn(pub + 1, EC_PUB_LEN / 2, NULL);
	BIGNUM *bn_pub_y = BN_bin2bn(pub + EC_PUB_LEN / 2 + 1, EC_PUB_LEN / 2, NULL);

	if (key == NULL)
		return (NULL);

	if (group == NULL || point == NULL)
	{
		free_them_all(key, group, NULL, NULL, NULL);
		return (NULL);
	}
	if (bn_pub_x == NULL || bn_pub_y == NULL)
	{
		free_them_all(key, group, point, bn_pub_x, bn_pub_y);
		return (NULL);
	}
	if (!EC_POINT_set_affine_coordinates_GFp(group, point, bn_pub_x,
						bn_pub_y, NULL))
	{
		free_them_all(key, group, point, bn_pub_x, bn_pub_y);
		return (NULL);
	}
	if (!EC_KEY_set_group(key, group))
	{
		free_them_all(key, group, point, bn_pub_x, bn_pub_y);
		return (NULL);
	}
	if (!EC_KEY_set_public_key(key, point))
	{
		free_them_all(key, group, point, bn_pub_x, bn_pub_y);
		return (NULL);
	}

	free_them_all(NULL, group, point, bn_pub_x, bn_pub_y);
	return (key);
}

void free_them_all(EC_KEY *key, EC_GROUP *group, EC_POINT *point,
			BIGNUM *bn_pub_x, BIGNUM *bn_pub_y)
{
	if (key != NULL)
		EC_KEY_free(key);

	if (group != NULL)
		EC_GROUP_free(group);

	if (point != NULL)
		EC_POINT_free(point);

	if (bn_pub_x != NULL)
		BN_free(bn_pub_x);

	if (bn_pub_y != NULL)
		BN_free(bn_pub_y);
}
