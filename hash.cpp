#include "stdafx.h"

#include "spasm.h"
#include "hash.h"
#include "storage.h"

/* 
 * Strong hash function for English language (such as line labels)
 * Austin Appleby (murmurhash.googlepages.com)
 */
#define ROTL32(x,y) ((x << y) | (x >> (32 - y)))

/* Useful to override if alignment or endianness must be accounted for. */
static inline uint32_t getblock32(const uint32_t *p, int i) {
    return p[i];
}

// Finalization mix - force all bits of a hash block to avalanche
static inline uint32_t fmix32 ( uint32_t h ) {
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

void MurmurHash3_x86_32 ( const void * key, int len,
                          uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 4;

  uint32_t h1 = seed;

  const uint32_t c1 = 0xcc9e2d51;
  const uint32_t c2 = 0x1b873593;

  //----------
  // body

  const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

  for(int i = -nblocks; i; i++)
  {
    uint32_t k1 = getblock32(blocks,i);

    k1 *= c1;
    k1 = ROTL32(k1,15);
    k1 *= c2;
   
    h1 ^= k1;
    h1 = ROTL32(h1,13);
    h1 = h1*5+0xe6546b64;
  }

  //----------
  // tail

  const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

  uint32_t k1 = 0;

  switch(len & 3)
  {
  case 3: k1 ^= tail[2] << 16;
  case 2: k1 ^= tail[1] << 8;
  case 1: k1 ^= tail[0];
          k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
  };

  //----------
  // finalization

  h1 ^= len;

  h1 = fmix32(h1);

  *(uint32_t*)out = h1;
} 

hash_t::hash_t(void (*remove_callback)(void *)) : 
        std::unordered_map<const char *, void *, mystringhash, myequalto>() {
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
    ht->insert(std::make_pair(key->name, store));
}


/*
 * Looks up a value from a hash table
 * returns NULL if not found
 */
void *hash_lookup (hash_t *ht, const char *name) {
    auto location = ht->find(name);
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
    auto location = ht->find(name);
    if (location == ht->end()) {
        return 0;
    }

    ht->remove_callback(location->second);
    ht->erase(location);
    return 1;
}

void hash_enum (hash_t *ht, void enum_callback(void *, void *), void *arg) {
    for (auto i = ht->begin(); i != ht->end(); i++) {
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
    for (auto i = ht->begin(); i != ht->end(); i++) {
        ht->remove_callback(i->second);
    }
    delete ht;
}
