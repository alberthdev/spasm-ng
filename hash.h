#ifndef HASH_H_
#define HASH_H_

#include <stdint.h>
#include <map>
#include "list.h"

typedef struct {
	char *name;
} store_t;

struct comparator
{
    bool operator()(const char * _Left, const char *_Right) const
    {
        if (strcmp(_Left, _Right) < 0)
            return true;
        else
            return false;
    }
};

typedef std::map<const char *, void *, comparator> htt_base;

class hash_t : public htt_base {
public:
	void (*remove_callback)(void *);

    hash_t(void (*remove_callback)(void *));
};

typedef void (*HASH_ENUM_CALLBACK)(void *, void *);
typedef void (*HASH_REMOVE_CALLBACK)(void *);

hash_t *hash_init (void remove_callback(void *));
void hash_insert (hash_t *ht, void *store);
void *hash_lookup (hash_t *ht, const char *name);
int hash_remove (hash_t *ht, const char *name);
void hash_enum (hash_t *ht, void enum_callback(void *, void *), void *arg);
int hash_count (hash_t *ht);
void hash_free (hash_t *ht);

#endif /*HASH_H_*/
