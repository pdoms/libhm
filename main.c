#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include "hm.h"
#include<stdint.h>
#include<string.h>

//I was just playing around here in the main.c file. It's not part of the lib.

int main() {
    char keys[10] = "abcdefghij";
    hm* hashmap = hm_new();
    for (int i =0; i < 10; ++i) {
        char* c = keys + i;
        char s[6] = "key_";
        s[4] = *c;
        hm_set(hashmap, s, c);
    }
    assert(hm_len(hashmap) == 10);
    hmi iter = hm_iterator(hashmap);
    while (hm_iter_next(&iter)) {
        printf("key: %s, value: %c\n", iter.key, *(int*)iter.value);
    }

    hm_destroy(hashmap);

    return 0;
}
