/* hash.c: hash functions */

#include "hash.h"

#include <stdio.h>

/**
 * Constants
 * http://isthe.com/chongo/tech/comp/fnv/
 */

#define FNV_OFFSET_BASIS    (0xcbf29ce484222325ULL)
#define FNV_PRIME           (0x100000001b3ULL)

/**
 * Compute FNV-1 hash.
 * @param   data            Data to hash.
 * @param   n               Number of bytes in data.
 * @return  Computed hash as 64-bit unsigned integer.
 */
uint64_t    hash_from_data(const void *data, size_t n) {
    uint8_t *dataBytes = (uint8_t *)data;

    uint64_t hash = FNV_OFFSET_BASIS;
    for (size_t i = 0; i < n; ++i) {
        hash = hash ^ *(dataBytes++);
        hash = hash * FNV_PRIME;
    }

    return hash;
}

/**
 * Compute MD5 digest.
 * @param   path            Path to file to checksum.
 * @param   hexdigest       Where to store the computed checksum in hexadecimal.
 * @return  Whether or not the computation was successful.
 */
bool        hash_from_file(const char *path, char hexdigest[HEX_DIGEST_LENGTH]) {
    FILE *stream = fopen(path, "r");
    if (!stream) return false;
    
    MD5_CTX context;
    uint8_t buffer[BUFSIZ];
    size_t bytes;
    uint8_t digest[MD5_DIGEST_LENGTH];

    MD5_Init(&context);
    bytes = fread(buffer, sizeof(buffer[0]), BUFSIZ, stream);
    while (bytes > 0) {
        MD5_Update(&context, buffer, bytes);
        bytes = fread(buffer, sizeof(buffer[0]), BUFSIZ, stream);
    }
    if (fclose(stream) == EOF) return false;

    MD5_Final(digest, &context);

    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        sprintf(hexdigest + i*2, "%02x", digest[i]);
    }

    return true;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
