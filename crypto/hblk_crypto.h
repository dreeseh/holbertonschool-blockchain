#ifndef _HBLK_CRYPTO_H
#define _HBLK_CRYPTO_H

/* libraries */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>
#include <openssl/err.h>

/* macros */
# define EC_CURVE   NID_secp256k1

/* EC_KEY public key octet string length (using 256-bit curve) */
# define EC_PUB_LEN 65
/* Maximum signature octet string length (using 256-bit curve) */
# define SIG_MAX_LEN    72

# define PRI_FILENAME   "key.pem"
# define PUB_FILENAME   "key_pub.pem"

/* data structures */
/**
 * struct sig_s - EC Signature structure
 *
 * @sig: Signature buffer. The whole space may not be used
 * @len: Actual signature size. Can't exceed SIG_MAX_LEN, therefore stored on a byte
 */
typedef struct sig_s
{
    /*
     * @sig must stay first, so we can directly use the structure as
     * an array of char
     */
    uint8_t     sig[SIG_MAX_LEN];
    uint8_t     len;
} sig_t;

/* prototypes */
uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]);
EC_KEY *ec_create(void);

#endif /* _HBLK_CRYPTO_H */