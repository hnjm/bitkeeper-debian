/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtomcrypt.com
 */
#include "tomcrypt.h"

/**
  @file ctr_decrypt.c
  CTR implementation, decrypt data, Tom St Denis
*/

#ifdef CTR

/**
   CTR decrypt
   @param ct      Ciphertext
   @param pt      [out] Plaintext
   @param len     Length of ciphertext (octets)
   @param ctr     CTR state
   @return CRYPT_OK if successful
*/
int ctr_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_CTR *ctr)
{
   LTC_ARGCHK(pt != NULL);
   LTC_ARGCHK(ct != NULL);
   LTC_ARGCHK(ctr != NULL);

   return ctr_encrypt(ct, pt, len, ctr);
}

#endif


/* $Source: /cvs/libtom/libtomcrypt/src/modes/ctr/ctr_decrypt.c,v $ */
/* $Revision: 1.4 $ */
/* $Date: 2006/03/31 14:15:35 $ */
