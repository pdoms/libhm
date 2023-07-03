#define HM_IMPLEMENTATION
#include "hm.h"

int main() {
    char keys[10] = "abcdefghij";
    hm* hashmap = hm_new();
    assert(hm_get(hashmap, "key") == NULL);


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
    printf("get ok\n");
    int removed = hm_remove(hashmap, "key_c");
    assert(removed == 1);
    assert(hm_get(hashmap, "key_c") == NULL);
    assert(hm_len(hashmap) == 9);
    printf("remove ok\n");
    hm_destroy(hashmap);






    char* key = "username";
    double value = 12.90988;
    hm* hashm = hm_new();
    hm_set(hashm, key, &value);

    double* retrieved = (double*)hm_get(hashm, key);
    assert(*retrieved == value);
    hm_destroy(hashm);
    printf("numeric ok\n");
    hm* ht = hm_new();
    char* k1 = "key1";
    char* v1 = "first_value";
    char* k2 = "key2";
    char* v2 = "second_value";
    
    hm_set(ht, k1, v1);
    hm_set(ht, k2, v2);
    
    char expect[] = "key1 first_value\nkey2 second_value\n";
    uint8_t buffer[1024];
    int len = hm_serialize_cstr(ht, buffer, 1024, 32, 10);
    for (int i =0; i < strlen(expect); ++i) {
        assert(expect[i] == (char)buffer[i]);
    }
    assert(strlen(expect) == len);

    printf("serialize ok\n");


    return 0;
}
