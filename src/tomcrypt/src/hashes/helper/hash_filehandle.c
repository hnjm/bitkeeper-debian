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
#include <unistd.h>
#include "tomcrypt.h"

/**
   @file hash_filehandle.c
   Hash open files, Tom St Denis
*/

/** 
  Hash data from an open file handle.  
  @param hash   The index of the hash you want to use
  @param in     The FILE* handle of the file you want to hash
  @param out    [out] The destination of the digest
  @param outlen [in/out] The max size and resulting size of the digest
  @result CRYPT_OK if successful   
*/
int hash_fd(int hash, int fd, unsigned char *out, unsigned long *outlen)
{
#ifdef LTC_NO_FILE
    return CRYPT_NOP;
#else
    hash_state md;
    unsigned char buf[8192];
    size_t x;
    int err;

    LTC_ARGCHK(out    != NULL);
    LTC_ARGCHK(outlen != NULL);

    if ((err = hash_is_valid(hash)) != CRYPT_OK) {
        return err;
    }

    if (*outlen < hash_descriptor[hash].hashsize) {
       *outlen = hash_descriptor[hash].hashsize;
       return CRYPT_BUFFER_OVERFLOW;
    }
    if ((err = hash_descriptor[hash].init(&md)) != CRYPT_OK) {
       return err;
    }

    *outlen = hash_descriptor[hash].hashsize;
    while ((x = read(fd, buf, sizeof(buf))) > 0) {
        if ((err = hash_descriptor[hash].process(&md, buf, x)) != CRYPT_OK) {
           return err;
        }
    }
    err = hash_descriptor[hash].done(&md, out);

#ifdef LTC_CLEAN_STACK
    zeromem(buf, sizeof(buf));
#endif
    return err;
#endif
}


/* $Source: /cvs/libtom/libtomcrypt/src/hashes/helper/hash_filehandle.c,v $ */
/* $Revision: 1.5 $ */
/* $Date: 2006/06/16 21:53:41 $ */
