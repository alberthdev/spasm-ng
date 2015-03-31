#include "stdafx.h"

#include "spasm.h"
#include "hash.h"
#include "storage.h"

hash_t::hash_t(void (*remove_callback)(void *)) : htt_base() {
    this->remove_callback = remove_callback;
}

/*
 * Creates a new hash table with an upper bound size
 */
hash_t *hash_init (size_t size, void remove_callback(void *)) {
    hash_t *ht = new hash_t(remove_callback);
    return ht;
}


/*
 * Inserts a value into a hash table.
 *
 * `store` is the value to be taken, where its first element is assumed
 * to be a store_t providing the key.
 */
void hash_insert (hash_t *ht, void *store) {
    store_t *key = (store_t *)store;
    (*ht)[key->name] = store;
}


/*
 * Looks up a value from a hash table
 * returns NULL if not found
 */
void *hash_lookup (hash_t *ht, const char *name) {
    hash_t::iterator location = ht->find(name);
    if (location == ht->end()) {
        return NULL;
    } else {
        return location->second;
    }
}


/*
 * Removes a hash from a hash table
 *
 * Returns 1 on success, or 0 if the name doesn't exist.
 */
int hash_remove (hash_t *ht, const char *name) {
    hash_t::iterator location = ht->find(name);
    if (location == ht->end()) {
        return 0;
    }

    ht->remove_callback(location->second);
    ht->erase(location);
    return 1;
}

void hash_enum (hash_t *ht, void enum_callback(void *, void *), void *arg) {
    for (hash_t::iterator i = ht->begin(); i != ht->end(); i++) {
        enum_callback(i->second, arg);
    }
}

int hash_count (hash_t *ht) {
    return ht->size();
}

/*
 * Free a hash table, removing elements
 */
void hash_free (hash_t *ht) {
    // Invoke all the remove callbacks.
    // This invalidates all of the map's contents.
    for (hash_t::iterator i = ht->begin(); i != ht->end(); i++) {
        ht->remove_callback(i->second);
    }
    delete ht;
}
