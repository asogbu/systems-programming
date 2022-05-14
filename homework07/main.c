/* main.c: string library utility */

#include "str.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Flags */

enum {
    /* Enumerate Flags */
    STRIP = 1<<0,
    REVERSE = 1<<1,
    LOWER = 1<<2,
    UPPER = 1<<3,
    TITLE = 1<<4
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s      Strip whitespace\n");
    fprintf(stderr, "   -r      Reverse line\n");
    fprintf(stderr, "   -l      Convert to lowercase\n");
    fprintf(stderr, "   -u      Convert to uppercase\n");
    fprintf(stderr, "   -t      Convert to titlecase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int flag) {
    /* Process each line in stream by performing transformations */
    while (!feof(stream)) {
        char line[BUFSIZ];
        if (!fgets(line, BUFSIZ, stream)) break;
        
        str_chomp(line);
        if (source && target) str_translate(line, source, target);
        if (flag & STRIP) str_strip(line);
        if (flag & REVERSE) str_reverse(line);
        if (flag & LOWER) str_lower(line);
        if (flag & UPPER) str_upper(line);
        if (flag & TITLE) str_title(line);

        puts(line);
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    PROGRAM_NAME = argv[0];

    /* Parse command line arguments */
    int argind;
    int flag = 0;
    for (argind = 1; argind < argc; ++argind) {
        char *arg = argv[argind];
        if ((strlen(arg) == 2) && (*arg == '-')) ++arg;
        else break;

        switch (*arg) {
            case 's': flag |= STRIP;
                break;
            case 'r': flag |= REVERSE;
                break;
            case 'l': flag |= LOWER;
                break;
            case 'u': flag |= UPPER;
                break;
            case 't': flag |= TITLE;
                break;
            case 'h': usage(EXIT_SUCCESS);
                break;
            default: usage(EXIT_FAILURE);
                break;
        }
    }
    
    char *source = NULL;
    char *target = NULL;
    if (argind < argc) {
        source = argv[argind++];
        if (argind < argc) target = argv[argind++];
        else usage(EXIT_FAILURE);
    }

    if (argind < argc) usage(EXIT_FAILURE);

    /* Translate Stream */
    translate_stream(stdin, source, target, flag);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
