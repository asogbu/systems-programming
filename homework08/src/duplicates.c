/* duplicates.c */

#include "hash.h"
#include "table.h"
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Type Definitions */
typedef struct {
    bool count;
    bool quiet;
} Options;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s paths...\n", PROGRAM_NAME);
    fprintf(stderr, "   -c      Only display total number of duplicates\n");
    fprintf(stderr, "   -q      Do not write anything (exit with 0 if duplicate found)\n");
    exit(status);
}

bool is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) == 0) {
        return ((statbuf.st_mode & S_IFMT) == S_IFDIR);
    } else {
        fprintf(stderr, "stat: %s\n", strerror(errno));
        return false;
    }
}

size_t check_file(const char *path, Table *checksums, Options *options) {
    char hexdigest[HEX_DIGEST_LENGTH];
    if (!(hash_from_file(path, hexdigest))) {
        fprintf(stderr, "hash_from_file: %s\n", strerror(errno));
        return 0;
    }

    Value * searchValue = table_search(checksums, hexdigest);
    if (searchValue) {
        if (options->quiet) exit(0);
        if (!(options->count)) fprintf(stdout, "%s is duplicate of %s\n", path, searchValue->string);
        return 1;
    } else {
        table_insert(checksums, hexdigest, (Value)(char *)path, STRING);
        return 0;
    }
}

size_t check_directory(const char *root, Table *checksums, Options *options) {
    size_t duplicates = 0;

    /* Open directory handle */
    DIR *d = opendir(root);
    if (!d) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 0;
    }

    /* For each directory entry, check if it is a directory, call check_directory or check_file */
    for (struct dirent *e = readdir(d); e; e = readdir(d)) {
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) continue;

        /* Construct full path to file */
        char path[BUFSIZ];
        sprintf(path, "%s/%s", root, e->d_name);

        if (is_directory(path)) duplicates += check_directory(path, checksums, options);
        else duplicates += check_file(path, checksums, options);
    }

    /* Close directory handle */
    closedir(d);

    return duplicates;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    PROGRAM_NAME = argv[0];

    /* Parse command line arguments */
    int argind;
    Options options = {false, false};
    for (argind = 1; argind < argc; ++argind) {
        char *arg = argv[argind];
        if ((strlen(arg) == 2) && (*arg == '-')) ++arg;
        else break;

        switch (*arg) {
            case 'c': options.count = true;
                break;
            case 'q': options.quiet = true;
                break;
            case 'h': usage(EXIT_SUCCESS);
                break;
            default: usage(EXIT_FAILURE);
                break;
        }
    }

    /* Find Duplicates */
    Table * checksums = table_create(0);
    if (!checksums) {
        fprintf(stderr, "table_create: Unable to allocate table\n");
        return EXIT_FAILURE;
    }

    size_t duplicates = 0;

    while (argind < argc) {
        char * path = argv[argind];
        if (is_directory(path)) duplicates += check_directory(path, checksums, &options);
        else duplicates += check_file(path, checksums, &options);
        argind++;
    }
    table_delete(checksums);
    if (options.quiet) return 1;
    if (options.count) fprintf(stdout, "%lu\n", duplicates);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
