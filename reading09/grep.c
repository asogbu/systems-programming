/* grep.c */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s PATTERN\n", PROGRAM_NAME);
    exit(status);
}

bool grep_stream(FILE *stream, char * search) {
    char buffer[BUFSIZ];
    bool found = false;

    while (fgets(buffer, BUFSIZ, stream)) {
        if (strstr(buffer, search) != NULL) {
            found = true;
            fputs(buffer, stdout);
        }
    }

    return found;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }

    char * search;
    if (argind < argc) search = argv[argind];
    else usage(1);

    /* Process each file */
    return !grep_stream(stdin, search);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
