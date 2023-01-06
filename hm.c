#include "hm.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16;
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

hm* hm_new(void) 
{
    
    hm* map = malloc(sizeof(hm));
    if (map == NULL) {
        return NULL;
    }
    map->length = 0;
    map->capacity = INITIAL_CAPACITY;
    map->entries = calloc(map->capacity, sizeof(hm_entry));
    if (map->entries == NULL) {
        free(map);
        return NULL;
    }
    return map;
}

void hm_destroy(hm* map) 
{
    for (size_t i = 0; i < map->capacity; i++) {
        free((void*)map->entries[i].key);
    }   
    free(map->entries);
    free(map);
}

static uint64_t FNV_1A(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

//wrapper function, in case I use a different one later on
static uint64_t hasher(const char* key) 
{
    return FNV_1A(key);

}



void* hm_get(hm* map, const char* key) 
{
    uint64_t hash = hasher(key);
    size_t index = (size_t) (hash & (uint64_t)(map->capacity - 1));
    while (map->entries[index].key != NULL) {
        if (strcmp(key, map->entries[index].key) == 0) {
            return map->entries[index].value;
        } else {
            index++;
            if (index >= map->capacity) {
                index=0;
            }
        }
    }
    return NULL;
}

static const char* hm_set_entry(hm_entry *entries, size_t capacity, const char* key, void* value, size_t* plength) 
{
    uint64_t hash = hasher(key);   
    size_t index = (size_t)(hash & (uint64_t)(capacity-1));


    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            // found key -> update value
            entries[index].value = value;
            return entries[index].key;
        }
        //move on if not found
        index++;
        //wrap at end
        if (index >= capacity) {
            index =0;
        }
    }

    // if key wasn't found, allocate and copy, then insert
    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }
    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
}

static bool hm_expand(hm* map) 
{
    size_t new_capacity = map->capacity*2;
    if (new_capacity < map->capacity) {
        return false; //overflow!!!
     }
    hm_entry* new_entries = calloc(new_capacity, sizeof(hm_entry));
    if (new_entries == NULL) {
        return false;
    }

    for (size_t i = 0; i < map->capacity; i++) {
        hm_entry entry = map->entries[i];
        if (entry.key != NULL) {
            hm_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
        }
    }

    free(map->entries);
    map->entries = new_entries;
    map->capacity = new_capacity;
    return true;
}


const char* hm_set(hm* map, const char* key, void* value) 
{
    if (value == NULL) {
        return NULL;
    }

    if (map->length >= map->capacity) {
        if (!hm_expand(map)) {
            return NULL;
        }
    }

    return hm_set_entry(map->entries, map->capacity, key, value, &map->length); 
}

size_t hm_len(hm* map) {
    return map->length;
}

hmi hm_iterator(hm* map) {
    hmi iter;
    iter._map = map;
    iter._index = 0;
    return iter;
}

bool hm_iter_next(hmi* iter) {
    hm* map = iter->_map;
    while (iter->_index < map->capacity) {
        size_t i = iter->_index;
        iter->_index++;
        if (map->entries[i].key != NULL) {
            hm_entry entry = map->entries[i];
            iter->key = entry.key;
            iter->value = entry.value;
            return true;
        }
    }
    return false;
}










