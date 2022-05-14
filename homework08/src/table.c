/* table.c: Separate Chaining Hash Table */

#include "table.h"
#include "hash.h"
#include "macros.h"

/**
 * Create Table data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @return  Allocated Table structure.
 */
Table *	    table_create(size_t capacity) {
    // Allocate table in heap
    Table *new_table = (Table *)malloc(sizeof(Table));
    if (!new_table) return NULL; // Check if fail

    // Set size
    new_table->size = 0;

    // Set capacity
    if (capacity == 0) new_table->capacity = DEFAULT_CAPACITY;
    else new_table->capacity = capacity;

    // Allocate buckets array of Pairs
    new_table->buckets = (Pair *)calloc(new_table->capacity, sizeof(Pair));
    if (!(new_table->buckets)) { // Check if fail
        free(new_table);
        return NULL;
    }

    return new_table;
}

/**
 * Delete Table data structure.
 * @param   t               Table data structure.
 * @return  NULL.
 */
Table *	    table_delete(Table *t) {
    for (size_t i = 0; i < t->capacity; ++i) pair_delete(((t->buckets)[i]).next, true);
    free(t->buckets);
    free(t);

    return NULL;
}

/**
 * Insert or update Pair into Table data structure.
 * @param   t               Table data structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   type            Pair's value's type.
 */
void        table_insert(Table *t, const char *key, const Value value, Type type) {
    uint64_t bucket = hash_from_data(key, strlen(key)) % t->capacity;

    for (Pair *curr = ((t->buckets)[bucket]).next; curr; curr = curr->next) {
        if (streq(curr->key, key)) {
            pair_update(curr, value, type);
            return;
        }
    }

    ((t->buckets)[bucket]).next = pair_create(key, value, ((t->buckets)[bucket]).next, type);
    (t->size)++;
}

/**
 * Search Table data structure by key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to search for.
 * @return  Pointer to the Value associated with specified key (or NULL if not found).
 */
Value *     table_search(Table *t, const char *key) {
    uint64_t bucket = hash_from_data(key, strlen(key)) % t->capacity;

    for (Pair *curr = ((t->buckets)[bucket]).next; curr; curr = curr->next) {
        if (streq(curr->key, key)) {
            return &(curr->value);
        }
    }

    return NULL;
}

/**
 * Remove Pair from Table data structure with specified key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to remove.
 * return   Whether or not the removal was successful.
 */
bool        table_remove(Table *t, const char *key) {
    uint64_t bucket = hash_from_data(key, strlen(key)) % t->capacity;

    Pair *prev = &((t->buckets)[bucket]);
    for (Pair *curr = ((t->buckets)[bucket]).next; curr; curr = curr->next) {
        if (streq(curr->key, key)) {
            prev->next = curr->next;
            pair_delete(curr, false);
            (t->size)--;
            return true;
        }
        prev = curr;
    }

    return false;
}

/**
 * Format all the entries in the Table data structure.
 * @param   m               Table data structure.
 * @param   stream          File stream to write to.
 */
void	    table_format(Table *t, FILE *stream) {
    for (size_t i = 0; i < t->capacity; ++i) {
        for (Pair *curr = ((t->buckets)[i]).next; curr; curr = curr->next) {
            pair_format(curr, stream);
        }
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
