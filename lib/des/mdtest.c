/*
 * Copyright (c) 1995, 1996 Kungliga Tekniska Hoegskolan (Royal Institute
 * of Technology, Stockholm, Sweden).
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the Kungliga Tekniska
 *      Hoegskolan and its contributors.
 * 
 * 4. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
RCSID("$Id$");
#endif

#include <stdio.h>
#include <string.h>
#include <md4.h>
#include <md5.h>
#include <sha.h>

int
md4_tests ()
{
  struct test {
    char *str;
    unsigned char hash[16];
  } tests[] = {
    {"", 
     {0x31, 0xd6, 0xcf, 0xe0, 0xd1, 0x6a, 0xe9, 0x31, 0xb7, 0x3c, 0x59, 
      0xd7, 0xe0, 0xc0, 0x89, 0xc0}},
    {"a",
     {0xbd, 0xe5, 0x2c, 0xb3, 0x1d, 0xe3, 0x3e, 0x46, 0x24, 0x5e, 0x05,
      0xfb, 0xdb, 0xd6, 0xfb, 0x24}},
    {"abc",
     {0xa4, 0x48, 0x01, 0x7a, 0xaf, 0x21, 0xd8, 0x52, 0x5f, 0xc1, 0x0a, 0xe8, 0x7a, 0xa6, 0x72, 0x9d}},
    {"message digest",
     {0xd9, 0x13, 0x0a, 0x81, 0x64, 0x54, 0x9f, 0xe8, 0x18, 0x87, 0x48, 0x06, 0xe1, 0xc7, 0x01, 0x4b}},
    {"abcdefghijklmnopqrstuvwxyz", {0xd7, 0x9e, 0x1c, 0x30, 0x8a, 0xa5, 0xbb, 0xcd, 0xee, 0xa8, 0xed, 0x63, 0xdf, 0x41, 0x2d, 0xa9, }},
    {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
     {0x04, 0x3f, 0x85, 0x82, 0xf2, 0x41, 0xdb, 0x35, 0x1c, 0xe6, 0x27, 0xe1, 0x53, 0xe7, 0xf0, 0xe4}},
    {"12345678901234567890123456789012345678901234567890123456789012345678901234567890",
     {0xe3, 0x3b, 0x4d, 0xdc, 0x9c, 0x38, 0xf2, 0x19, 0x9c, 0x3e, 0x7b, 0x16, 0x4f, 0xcc, 0x05, 0x36, }},
    {NULL, { 0x0 }}};
  struct test *t;

  printf ("md4... ");
  for (t = tests; t->str; ++t) {
    struct md4 md4;
    char res[16];

    md4_init (&md4);
    md4_update (&md4, t->str, strlen(t->str));
    md4_finito (&md4, res);
    if (memcmp (res, t->hash, 16) != 0) {
      printf ("MD4(\"%s\") failed\n", t->str);
      return 1;
    }
  }
  printf ("success\n");
  return 0;
}

int
md5_tests ()
{
  struct test {
    char *str;
    unsigned char hash[16];
  } tests[] = {
    {"", {0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04, 0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e}}, 
    {"a", {0x0c, 0xc1, 0x75, 0xb9, 0xc0, 0xf1, 0xb6, 0xa8, 0x31, 0xc3, 0x99, 0xe2, 0x69, 0x77, 0x26, 0x61}}, 
    {"abc", {0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0, 0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72}}, 
    {"message digest", {0xf9, 0x6b, 0x69, 0x7d, 0x7c, 0xb7, 0x93, 0x8d, 0x52, 0x5a, 0x2f, 0x31, 0xaa, 0xf1, 0x61, 0xd0}}, 
    {"abcdefghijklmnopqrstuvwxyz", {0xc3, 0xfc, 0xd3, 0xd7, 0x61, 0x92, 0xe4, 0x00, 0x7d, 0xfb, 0x49, 0x6c, 0xca, 0x67, 0xe1, 0x3b}}, 
    {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", {0xd1, 0x74, 0xab, 0x98, 0xd2, 0x77, 0xd9, 0xf5, 0xa5, 0x61, 0x1c, 0x2c, 0x9f, 0x41, 0x9d, 0x9f}}, 
    {"12345678901234567890123456789012345678901234567890123456789012345678901234567890", {0x57, 0xed, 0xf4, 0xa2, 0x2b, 0xe3, 0xc9, 0x55, 0xac, 0x49, 0xda, 0x2e, 0x21, 0x07, 0xb6, 0x7a}}, 
    {NULL, { 0x0 }}};
  struct test *t;

  printf ("md5... ");
  for (t = tests; t->str; ++t) {
    struct md5 md5;
    char res[16];

    md5_init (&md5);
    md5_update (&md5, t->str, strlen(t->str));
    md5_finito (&md5, res);
    if (memcmp (res, t->hash, 16) != 0) {
      printf ("MD5(\"%s\") failed\n", t->str);
      return 1;
    }
  }
  printf ("success\n");
  return 0;
}

int
sha_tests ()
{
  struct test {
    char *str;
    unsigned char hash[20];
  } tests[] = {
    {"abc", {0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A,
	     0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C,
	     0x9C, 0xD0, 0xD8, 0x9D}},
    {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
     {0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E,
      0xBA, 0xAE, 0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5,
      0xE5, 0x46, 0x70, 0xF1}},
    {NULL, { 0x0 }}};
  struct test *t;

  printf ("sha... ");
  for (t = tests; t->str; ++t) {
    struct sha sha;
    char res[20];

    sha_init (&sha);
    sha_update (&sha, t->str, strlen(t->str));
    sha_finito (&sha, res);
    if (memcmp (res, t->hash, 16) != 0) {
      printf ("SHA(\"%s\") failed\n", t->str);
      return 1;
    }
  }
  printf ("success\n");
  return 0;
}

int
main ()
{
  return md4_tests() + md5_tests() + sha_tests();
}
