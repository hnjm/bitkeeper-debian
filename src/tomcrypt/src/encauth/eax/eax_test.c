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

/** 
    @file eax_test.c
    EAX implementation, self-test, by Tom St Denis
*/
#include "tomcrypt.h"

#ifdef EAX_MODE

/**
   Test the EAX implementation
   @return CRYPT_OK if successful, CRYPT_NOP if self-testing has been disabled
*/
int eax_test(void)
{
#ifndef LTC_TEST
   return CRYPT_NOP;
#else
   static const struct {
       int               keylen, 
                       noncelen, 
                      headerlen, 
                         msglen;

       unsigned char        key[MAXBLOCKSIZE], 
                          nonce[MAXBLOCKSIZE], 
                         header[MAXBLOCKSIZE], 
                      plaintext[MAXBLOCKSIZE],
                     ciphertext[MAXBLOCKSIZE], 
                            tag[MAXBLOCKSIZE];
   } tests[] = {

/* NULL message */
{
   16, 0, 0, 0,
   /* key */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* nonce */
   { 0 },
   /* header */
   { 0 },
   /* plaintext */
   { 0 },
   /* ciphertext */
   { 0 },
   /* tag */
   { 0x9a, 0xd0, 0x7e, 0x7d, 0xbf, 0xf3, 0x01, 0xf5,
     0x05, 0xde, 0x59, 0x6b, 0x96, 0x15, 0xdf, 0xff }
},

/* test with nonce */
{
   16, 16, 0, 0,
   /* key */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* nonce */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* header */
   { 0 },
   /* plaintext */
   { 0 },
   /* ciphertext */
   { 0 },
   /* tag */
   { 0x1c, 0xe1, 0x0d, 0x3e, 0xff, 0xd4, 0xca, 0xdb,
     0xe2, 0xe4, 0x4b, 0x58, 0xd6, 0x0a, 0xb9, 0xec }
},

/* test with header [no nonce]  */
{
   16, 0, 16, 0,
   /* key */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* nonce */
   { 0 },
   /* header */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* plaintext */
   { 0 },
   /* ciphertext */
   { 0 },
   /* tag */
   { 0x3a, 0x69, 0x8f, 0x7a, 0x27, 0x0e, 0x51, 0xb0,
     0xf6, 0x5b, 0x3d, 0x3e, 0x47, 0x19, 0x3c, 0xff }
},

/* test with header + nonce + plaintext */
{
   16, 16, 16, 32,
   /* key */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* nonce */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },  
   /* header */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* plaintext */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
     0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f },
   /* ciphertext */
   { 0x29, 0xd8, 0x78, 0xd1, 0xa3, 0xbe, 0x85, 0x7b,
     0x6f, 0xb8, 0xc8, 0xea, 0x59, 0x50, 0xa7, 0x78,
     0x33, 0x1f, 0xbf, 0x2c, 0xcf, 0x33, 0x98, 0x6f,
     0x35, 0xe8, 0xcf, 0x12, 0x1d, 0xcb, 0x30, 0xbc },
   /* tag */
   { 0x4f, 0xbe, 0x03, 0x38, 0xbe, 0x1c, 0x8c, 0x7e,
     0x1d, 0x7a, 0xe7, 0xe4, 0x5b, 0x92, 0xc5, 0x87 }
},

/* test with header + nonce + plaintext [not even sizes!] */
{
   16, 15, 14, 29,
   /* key */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
   /* nonce */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e },  
   /* header */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d },
   /* plaintext */
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
     0x18, 0x19, 0x1a, 0x1b, 0x1c },
   /* ciphertext */
   { 0xdd, 0x25, 0xc7, 0x54, 0xc5, 0xb1, 0x7c, 0x59,
     0x28, 0xb6, 0x9b, 0x73, 0x15, 0x5f, 0x7b, 0xb8,
     0x88, 0x8f, 0xaf, 0x37, 0x09, 0x1a, 0xd9, 0x2c,
     0x8a, 0x24, 0xdb, 0x86, 0x8b },
   /* tag */
   { 0x0d, 0x1a, 0x14, 0xe5, 0x22, 0x24, 0xff, 0xd2,
     0x3a, 0x05, 0xfa, 0x02, 0xcd, 0xef, 0x52, 0xda }
},

/* Vectors from Brian Gladman */

{
   16, 16, 8, 0,
   /* key */
   { 0x23, 0x39, 0x52, 0xde, 0xe4, 0xd5, 0xed, 0x5f,
     0x9b, 0x9c, 0x6d, 0x6f, 0xf8, 0x0f, 0xf4, 0x78 },
   /* nonce */
   { 0x62, 0xec, 0x67, 0xf9, 0xc3, 0xa4, 0xa4, 0x07,
     0xfc, 0xb2, 0xa8, 0xc4, 0x90, 0x31, 0xa8, 0xb3 },
   /* header */
   { 0x6b, 0xfb, 0x91, 0x4f, 0xd0, 0x7e, 0xae, 0x6b },
   /* PT */
   { 0x00 },
   /* CT */
   { 0x00 },
   /* tag */
   { 0xe0, 0x37, 0x83, 0x0e, 0x83, 0x89, 0xf2, 0x7b,
     0x02, 0x5a, 0x2d, 0x65, 0x27, 0xe7, 0x9d, 0x01 }
},

{
   16, 16, 8, 2,
   /* key */ 
   { 0x91, 0x94, 0x5d, 0x3f, 0x4d, 0xcb, 0xee, 0x0b,
     0xf4, 0x5e, 0xf5, 0x22, 0x55, 0xf0, 0x95, 0xa4 },
   /* nonce */
   { 0xbe, 0xca, 0xf0, 0x43, 0xb0, 0xa2, 0x3d, 0x84,
     0x31, 0x94, 0xba, 0x97, 0x2c, 0x66, 0xde, 0xbd },
   /* header */
   { 0xfa, 0x3b, 0xfd, 0x48, 0x06, 0xeb, 0x53, 0xfa },
   /* PT */
   { 0xf7, 0xfb },
   /* CT */
   { 0x19, 0xdd },
   /* tag */
   { 0x5c, 0x4c, 0x93, 0x31, 0x04, 0x9d, 0x0b, 0xda,
     0xb0, 0x27, 0x74, 0x08, 0xf6, 0x79, 0x67, 0xe5 }
},

{
   16, 16, 8, 5,
   /* key */
   { 0x01, 0xf7, 0x4a, 0xd6, 0x40, 0x77, 0xf2, 0xe7,
     0x04, 0xc0, 0xf6, 0x0a, 0xda, 0x3d, 0xd5, 0x23 },
   /* nonce */
   { 0x70, 0xc3, 0xdb, 0x4f, 0x0d, 0x26, 0x36, 0x84,
     0x00, 0xa1, 0x0e, 0xd0, 0x5d, 0x2b, 0xff, 0x5e },
   /* header */
   { 0x23, 0x4a, 0x34, 0x63, 0xc1, 0x26, 0x4a, 0xc6 },
   /* PT */
   { 0x1a, 0x47, 0xcb, 0x49, 0x33 },
   /* CT */
   { 0xd8, 0x51, 0xd5, 0xba, 0xe0 },
   /* Tag */
   { 0x3a, 0x59, 0xf2, 0x38, 0xa2, 0x3e, 0x39, 0x19,
     0x9d, 0xc9, 0x26, 0x66, 0x26, 0xc4, 0x0f, 0x80 }
}   

};
   int err, x, idx, res;
   unsigned long len;
   unsigned char outct[MAXBLOCKSIZE], outtag[MAXBLOCKSIZE];

    /* AES can be under rijndael or aes... try to find it */ 
    if ((idx = find_cipher("aes")) == -1) {
       if ((idx = find_cipher("rijndael")) == -1) {
          return CRYPT_NOP;
       }
    }

    for (x = 0; x < (int)(sizeof(tests)/sizeof(tests[0])); x++) {
        len = sizeof(outtag);
        if ((err = eax_encrypt_authenticate_memory(idx, tests[x].key, tests[x].keylen,
            tests[x].nonce, tests[x].noncelen, tests[x].header, tests[x].headerlen,
            tests[x].plaintext, tests[x].msglen, outct, outtag, &len)) != CRYPT_OK) {
           return err;
        }
        if (memcmp(outct, tests[x].ciphertext, tests[x].msglen) || memcmp(outtag, tests[x].tag, len)) {
#if 0
           unsigned long y;
           printf("\n\nFailure: \nCT:\n");
           for (y = 0; y < (unsigned long)tests[x].msglen; ) {
               printf("0x%02x", outct[y]);
               if (y < (unsigned long)(tests[x].msglen-1)) printf(", ");
               if (!(++y % 8)) printf("\n");
           }
           printf("\nTAG:\n");
           for (y = 0; y < len; ) {
               printf("0x%02x", outtag[y]);
               if (y < len-1) printf(", ");
               if (!(++y % 8)) printf("\n");
           }
#endif
           return CRYPT_FAIL_TESTVECTOR;
        }

        /* test decrypt */
        if ((err = eax_decrypt_verify_memory(idx, tests[x].key, tests[x].keylen,
             tests[x].nonce, tests[x].noncelen, tests[x].header, tests[x].headerlen,
             outct, tests[x].msglen, outct, outtag, len, &res)) != CRYPT_OK) {
            return err;
        }
        if ((res != 1) || memcmp(outct, tests[x].plaintext, tests[x].msglen)) {
#if 0
           unsigned long y;
           printf("\n\nFailure (res == %d): \nPT:\n", res);
           for (y = 0; y < (unsigned long)tests[x].msglen; ) {
               printf("0x%02x", outct[y]);
               if (y < (unsigned long)(tests[x].msglen-1)) printf(", ");
               if (!(++y % 8)) printf("\n");
           }
           printf("\n\n");
#endif
           return CRYPT_FAIL_TESTVECTOR;
        }

     }
     return CRYPT_OK;
#endif /* LTC_TEST */
}

#endif /* EAX_MODE */

/* $Source: /cvs/libtom/libtomcrypt/src/encauth/eax/eax_test.c,v $ */
/* $Revision: 1.4 $ */
/* $Date: 2006/03/31 14:15:35 $ */
