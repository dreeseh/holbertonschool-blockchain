#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts the public key from an EC_KEY opaque structure
 *
 * @key: a pointer to the EC_KEY structure to retrieve the public key from
 * @pub: the address at which to store the extracted public key
 *
 * Return: a pointer to pub, or NULL upon failure
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *point;
	const EC_GROUP *group;
	size_t len;

	/* retrieves the public key point from key struct */
	point = EC_KEY_get0_public_key(key);

	/* retrieves the EC group fron key struct */
	group = EC_KEY_get0_group(key);

	/**
	 * The EC_POINT_point2oct function is used to convert the public
	 * key point into an uncompressed octet string.
	 * The resulting octet string is stored in the pub buffer
	 */
	len = EC_POINT_point2oct(group,
				 point,
				 POINT_CONVERSION_UNCOMPRESSED,
				 pub,
				 EC_PUB_LEN,
				 NULL);

	/* checks if key is null*/
	if (key == NULL)
		return (NULL);

	/* checks if point or group is null */
	if (point == NULL || group == NULL)
		return (NULL);

	/**
	 * checks if the length of the octet string matches
	 * EC_PUB_LEN (65) and returns NULL if it doesn't.
	 */
	if (len != EC_PUB_LEN)
		return (NULL);

	/* returning a pointer to the address of the extracted key */
	return (pub);
}
