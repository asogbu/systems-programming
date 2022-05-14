/* pair.c: Key/Value Pair */

#include "pair.h"

#include <stdlib.h>
#include <string.h>

/**
 * Create Pair structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   next            Reference to next pair.
 * @param   type            Pair's value's type.
 * @return  Allocated Pair structure.
 */
Pair *	    pair_create(const char *key, const Value value, Pair *next, Type type) {
    Pair *new_pair = (Pair *)malloc(sizeof(Pair));
    if (!new_pair) return NULL;

    new_pair->next = next;
    new_pair->key = strdup(key);
    new_pair->type = NUMBER;
    pair_update(new_pair, value, type);

    return new_pair;
}

/**
 * Delete Pair structure.
 * @param   p               Pair structure.
 * @param   recursive       Whether or not to delete remainder of pairs.
 * return   NULL.
 */
Pair *	    pair_delete(Pair *p, bool recursive) {
    if (!p) return NULL;
    if (recursive && p->next) pair_delete(p->next, true);

    free(p->key);
    if (p->type == STRING) free(p->value.string);
    free(p);

    return NULL;
}

/**
 * Update Pair's value.
 * @param   p               Pair structure.
 * @param   value           New value for Pair.
 * @param   type            New value's type.
 */
void        pair_update(Pair *p, const Value value, Type type) {
    if (!p) return;
    if (p->type == STRING) free(p->value.string);
    if (type == STRING) p->value.string = strdup(value.string);
    else p->value = value;
    p->type = type;
}

/**
 * Format Pair by writing to stream.
 * @param   p               Pair structure.
 * @param   stream          File stream to write to.
 */
void        pair_format(Pair *p, FILE *stream) {
    if (!p) return;
    switch (p->type) {
        case NUMBER:
            fprintf(stream, "%s\t%ld\n", p->key, p->value.number);
            break;
        case STRING:
            fprintf(stream, "%s\t%s\n", p->key, p->value.string);
            break;
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
