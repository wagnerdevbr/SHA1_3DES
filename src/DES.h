
#ifndef DES_H
#define DES_H

#ifdef __cplusplus
extern "C" {
#endif
#include "Primitives.h"

/*
 * Encryption/Decryption context of DES
 */
typedef struct
{
  uint32 encrypt_subkeys[32];
  uint32 decrypt_subkeys[32];
} gl_des_ctx;

/*
 * Encryption/Decryption context of Triple-DES
 */
typedef struct
{
  uint32 encrypt_subkeys[96];
  uint32 decrypt_subkeys[96];
} gl_3des_ctx;

/* Check whether the 8 byte key is weak.  Does not check the parity
 * bits of the key but simple ignore them. */
int gl_des_is_weak_key (const unsigned char * key);

/*
 * DES
 * ---
 */

/* Fill a DES context CTX with subkeys calculated from 64bit KEY.
 * Does not check parity bits, but simply ignore them.  Does not check
 * for weak keys. */
void gl_des_setkey (gl_des_ctx *ctx, const unsigned char * key);

/* Electronic Codebook Mode DES encryption/decryption of data
 * according to 'mode'. */
void gl_des_ecb_crypt (gl_des_ctx *ctx, const unsigned char * from,  unsigned char * to, int mode);

#define gl_des_ecb_encrypt(ctx, from, to)  gl_des_ecb_crypt(ctx, from, to, 0)
#define gl_des_ecb_decrypt(ctx, from, to)  gl_des_ecb_crypt(ctx, from, to, 1)

/* Triple-DES
 * ----------
 */

/* Fill a Triple-DES context CTX with subkeys calculated from two
 * 64bit keys in KEY1 and KEY2.  Does not check the parity bits of the
 * keys, but simply ignore them.  Does not check for weak keys. */
void gl_3des_set2keys (gl_3des_ctx *ctx,
                  const unsigned char * key1,
                  const unsigned char * key2);

/*
 * Fill a Triple-DES context CTX with subkeys calculated from three
 * 64bit keys in KEY1, KEY2 and KEY3.  Does not check the parity bits
 * of the keys, but simply ignore them.  Does not check for weak
 * keys. */
void gl_3des_set3keys (gl_3des_ctx *ctx,
                  const unsigned char * key1,
                  const unsigned char * key2,
                  const unsigned char * key3);


/* Electronic Codebook Mode Triple-DES encryption/decryption of data
 * according to 'mode'.  Sometimes this mode is named 'EDE' mode
 * (Encryption-Decryption-Encryption). */
void gl_3des_ecb_crypt (gl_3des_ctx *ctx,
                   const unsigned char * from,
				   unsigned char * to,
                   int mode);

#define gl_3des_ecb_encrypt(ctx, from, to) gl_3des_ecb_crypt(ctx,from,to,0)
#define gl_3des_ecb_decrypt(ctx, from, to) gl_3des_ecb_crypt(ctx,from,to,1)

#ifdef __cplusplus
}
#endif

#endif /* DES_H */
