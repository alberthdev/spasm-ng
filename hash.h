#ifndef HASH_H_
#define HASH_H_

#include <stdint.h>
#include <unordered_map>
#include "list.h"

typedef struct {
	char *name;
} store_t;

void MurmurHash3_x86_32(const void *key, int len, uint32_t seed, void *out);

struct mystringhash
    : public std::unary_function<const char *, size_t>
{
    size_t operator()(const char* _Keyval) const
    {
        uint32_t out;
        MurmurHash3_x86_32(_Keyval, strlen(_Keyval), 0, &out);
        return (size_t)out;
    }
};

struct myequalto
    : public std::binary_function<const char *, const char *, bool>
{
    bool operator()(const char * _Left, const char *_Right) const
    {
        return (strcmp(_Left, _Right) == 0) ? true: false;
    }
};

class hash_t : public std::unordered_map<const char *, void *, mystringhash, myequalto> {
public:
	void (*remove_callback)(void *);

    hash_t(void (*remove_callback)(void *));
};

typedef void (*HASH_ENUM_CALLBACK)(void *, void *);
typedef void (*HASH_REMOVE_CALLBACK)(void *);

hash_t *hash_init (size_t size, void remove_callback(void *));
void hash_insert (hash_t *ht, void *store);
void *hash_lookup (hash_t *ht, const char *name);
int hash_remove (hash_t *ht, const char *name);
void hash_enum (hash_t *ht, void enum_callback(void *, void *), void *arg);
int hash_count (hash_t *ht);
void hash_free (hash_t *ht);

#endif /*HASH_H_*/
