// Implementation taken from:
// https://benhoyt.com/writings/hash-table-in-c/
// https://github.com/benhoyt/ht
// Taken because I wanted to learn about it but ended up mostly typing over the 
// implementation (tutorial)

#ifndef _HM_H
    #define _HM_H
#include<stdlib.h>
#include<stdbool.h>

// entry, for now we keep it defined
typedef struct {
    const char* key; //key will be null if mem location is empty
    void* value;
} hm_entry;

// main hash table struct
typedef struct {
    hm_entry* entries;
    size_t capacity;
    size_t length;
} hm;

//create new hashmap
extern hm* hm_new(void);

//destroy hash table
extern void hm_destroy(hm *map);

//get item by key
extern void* hm_get(hm* map, const char* key);

//sets new entry as key value (neither can be NULL)
//if key present, override, else new created
//returns address of newly created key
extern const char* hm_set(hm* map, const char* key, void* value);

// get length of table
extern size_t hm_len(hm* map);


// hm iterator
typedef struct {
    const char* key;
    void* value;
    hm* _map;
    size_t _index; 
} hmi;

//get iterator 
extern hmi hm_iterator(hm* map);

//get next item in iterator
//returns false if no more items left
//hm can't be updated while iterating
extern bool hm_iter_next(hmi* iter); 

#endif //_HM_H
