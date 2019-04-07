#ifndef OAR_BASE64_H_
#define OAR_BASE64_H_

#include <stdio.h>
#include "contiki.h"

/*
 * Base64 Encode and Decode in C
 * 
 * A very popular way to encode binary data is Base64. 
 * The basis of this is an encoding table. T
 * here are 64 total characters that go into the tale. 
 * There are multiple implementations of base64 with slight differences. 
 * They are all the same except for the last two characters and line ending requirements. 
 * The first 62 characters are always “ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789”. 
 * PEM and MIME encoding are the most common and use “+/” as the last two characters. 
 * PEM and MIME may use the same characters but they have different maximum line lengths. 
 * 
 * https://nachtimwald.com/2017/11/18/base64-encode-and-decode-in-c/
 * john@nachtimwald.com (November 18, 2017)
 * 
 */

int oar_base64_encode(const char *in, char *en, size_t len);
int oar_base64_decode(const char *in, unsigned char *out, size_t outlen);

#endif // (OAR_JSON_TINY_H_)

