#include <md5.h>
#include <string.h>
#include <stdlib.h>

#include "bucket.h"

#include <stdio.h>

// Make an unused bucket initializing its key, hash and value
struct BUCKET make_new_bucket(char key[], void* valuep) {
    struct BUCKET new_bucket;
    new_bucket.is_used = 0;
    strncpy(new_bucket.key, key, KEY_SIGNIFICANT_CHAR);
    memcpy(new_bucket.key_hash, md5_digest_str(key).data, sizeof(new_bucket.key_hash));
    new_bucket.valuep = valuep;
    return new_bucket;
}

// Generates array of unused buckets. Ownership of the memory is transfered to the caller
struct BUCKET* make_bucket_array(int size){
    struct BUCKET* buckets = malloc(size * sizeof(struct BUCKET));
    for (int i = 0; i < size; i++){buckets[i] = (struct BUCKET){.is_used = 0};}
    return buckets;
}

void print_bucket(struct BUCKET* bucket, char value_format[]){
    if (bucket == NULL){printf("EMPTY BUCKET\n"); return;}
    char key[KEY_SIGNIFICANT_CHAR+1];
    strncpy(key, bucket->key, KEY_SIGNIFICANT_CHAR); key[KEY_SIGNIFICANT_CHAR] = '\0';
    printf("PRINTING BUCKET:\n");
    printf("Currently being used: %s\n", bucket->is_used ? "YES" : "NO");
    printf("Key: %s\n", key);
    printf("Hash: "); for (int i = 0; i < 16; i++){printf("%02x", bucket->key_hash[i]);} printf("\n");
    printf("Value: ");
    printf(value_format, *(char*)bucket->valuep);
    printf("\n");
}