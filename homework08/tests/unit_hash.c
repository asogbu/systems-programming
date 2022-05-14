/* unit_hash.c */

#include "hash.h"
#include "macros.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */

static struct {
    char *	key;
    uint64_t	hash;
} DATA_HASHES[] = {
    {"wake me up inside", 9048950985493973590UL},
    {"123"              , 5003431119771845851UL},
    {"deadool"          , 9030128678874230203UL},
    {"wolverine"        , 9749463647854691528UL},
    {NULL               , 0},
};

static struct {
    char *	path;
    char *	hexdigest;
} FILE_HASHES[] = {
    {"include/hash.h"   , "12da1bb257a7e9a5e6b78f42a3c93bfe"},
    {"include/macros.h" , "9331940d9bd8af21f9c0663b1d892530"},
    {"include/pair.h"   , "f376c4ec109ce551bbecb38a5a77cc75"},
    {"include/table.h"  , "a4bf553a658ee3e668c0e043fe177b24"},
    {NULL               , 0},
};

/* Tests */

int test_00_hash_from_data() {
    for (size_t i = 0; DATA_HASHES[i].key; i++) {
    	uint64_t hash = hash_from_data(DATA_HASHES[i].key, strlen(DATA_HASHES[i].key));
    	printf("%20s = 0x%lx\n", DATA_HASHES[i].key, hash);
    	assert(DATA_HASHES[i].hash == hash);
    }
    return EXIT_SUCCESS;
}

int test_01_hash_from_file() {
    for (size_t i = 0; FILE_HASHES[i].path; i++) {
        char hexdigest[HEX_DIGEST_LENGTH];
        assert(hash_from_file(FILE_HASHES[i].path, hexdigest));
    	printf("%20s = %s\n", FILE_HASHES[i].path, hexdigest);
        assert(streq(FILE_HASHES[i].hexdigest, hexdigest));
    }
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0  Test hash_from_data\n");
        fprintf(stderr, "    1  Test hash_from_file\n");
        return EXIT_FAILURE;
    }   

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;

    switch (number) {
        case 0:  status = test_00_hash_from_data(); break;
        case 1:  status = test_01_hash_from_file(); break;
        default: fprintf(stderr, "Unknown NUMBER: %d\n", number); break;
    }
    
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
