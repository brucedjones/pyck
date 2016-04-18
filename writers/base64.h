#ifndef _BASE64_H_
#define _BASE64_H_

#include <inttypes.h>
#include <string.h>

#define WHITESPACE 64
#define EQUALS     65
#define INVALID    66
 


int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);
int base64decode (char *in, size_t inLen, unsigned char *out, size_t *outLen);

#endif