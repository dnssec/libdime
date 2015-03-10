#ifndef CRYPTO_H
#define CRYPTO_H

#include "openssl/obj_mac.h"
#include "openssl/ec.h"
#include "openssl/ecdsa.h"
#include "openssl/pem.h"

#include "error.h"
#include "ed25519.h"


#define AES_256_PADDING_SIZE	16

#define EC_SIGNING_CURVE	NID_secp384r1
#define EC_ENCRYPT_CURVE	NID_secp384r1

#define ED25519_KEY_SIZE	32
#define ED25519_KEY_B64_SIZE	43
#define ED25519_SIG_SIZE	64
#define ED25519_SIG_B64_SIZE	86

// Wrappers around ED25519 functions
typedef struct {
	ed25519_secret_key private;
	ed25519_public_key public;
} ED25519_KEY;


// Initializion and finalization routines.
PUBLIC_FUNC_DECL(int,             crypto_init,              void);
PUBLIC_FUNC_DECL(void,            crypto_shutdown,          void);

// Generating, loading, and freeing elliptical curve keys.
PUBLIC_FUNC_DECL(EC_KEY *,        load_ec_privkey,          const char *filename, const EC_GROUP **gptr);
PUBLIC_FUNC_DECL(EC_KEY *,        generate_ec_keypair,      int signing);
PUBLIC_FUNC_DECL(void,            free_ec_key,              EC_KEY *key);

// EC signature routines.
PUBLIC_FUNC_DECL(unsigned char *, ec_sign_data,             const unsigned char *hash, size_t hlen, EC_KEY *key, size_t *siglen);
PUBLIC_FUNC_DECL(unsigned char *, ec_sign_sha_data,         const unsigned char *data, size_t dlen, unsigned int shabits, EC_KEY *key, size_t *siglen);
PUBLIC_FUNC_DECL(int,             verify_ec_signature,      const unsigned char *hash, size_t hlen, const unsigned char *sig, size_t slen, EC_KEY *key);
PUBLIC_FUNC_DECL(int,             verify_ec_sha_signature,  const unsigned char *data, size_t dlen, unsigned int shabits, const unsigned char *sig, size_t slen, EC_KEY *key);

// Other EC-related routines.
PUBLIC_FUNC_DECL(void *,          ecies_env_derivation,     const void *input, size_t ilen, void *output, size_t *olen);
PUBLIC_FUNC_DECL(int,             compute_ec_ephemeral_aes256_key, EC_KEY *key, EC_KEY *ephemeral, unsigned char *keybuf);

// EC key serialization/deserialization.
PUBLIC_FUNC_DECL(unsigned char *, serialize_ec_pubkey,      EC_KEY *key, size_t *outsize);
PUBLIC_FUNC_DECL(EC_KEY *,        deserialize_ec_pubkey,    const unsigned char *buf, size_t blen, int signing);
PUBLIC_FUNC_DECL(unsigned char *, serialize_ec_privkey,     EC_KEY *key, size_t *outsize);
PUBLIC_FUNC_DECL(EC_KEY *,        deserialize_ec_privkey,   const unsigned char *buf, size_t blen, int signing);

// ED25519 key routines.
PUBLIC_FUNC_DECL(ED25519_KEY *,   load_ed25519_privkey,     const char *filename);
PUBLIC_FUNC_DECL(ED25519_KEY *,   generate_ed25519_keypair, void);
PUBLIC_FUNC_DECL(int,             ed25519_sign_data,        const unsigned char *data, size_t dlen, ED25519_KEY *key, ed25519_signature sigbuf);
PUBLIC_FUNC_DECL(int,             ed25519_verify_sig,       const unsigned char *data, size_t dlen, ED25519_KEY *key, ed25519_signature sigbuf);
PUBLIC_FUNC_DECL(void,            free_ed25519_key,         ED25519_KEY *key);

// Symmetric encryption routines.
PUBLIC_FUNC_DECL(int,             encrypt_aes_256,          unsigned char *outbuf, const unsigned char *data, size_t dlen, const unsigned char *key, const unsigned char *iv);
PUBLIC_FUNC_DECL(int,             decrypt_aes_256,          unsigned char *outbuf, const unsigned char *data, size_t dlen, const unsigned char *key, const unsigned char *iv);

// Miscellaneous.
PUBLIC_FUNC_DECL(int,             get_random_bytes,         void *buf, size_t len);


#endif
