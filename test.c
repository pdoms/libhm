#define HM_IMPLEMENTATION
#include "hm.h"

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

    int value1 = *(int*)hm_get(hashmap, "key_e");
    int result = 'e';
    assert((char)value1 == (char)result);
    hm_destroy(hashmap);

    char* key = "username";
    double value = 12.90988;
    hm* hashm = hm_new();
    hm_set(hashm, key, &value);

    double* retrieved = (double*)hm_get(hashm, key);
    assert(*retrieved == value);


    printf("ok\n");


    return 0;
}
