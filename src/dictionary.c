#include <stdlib.h>

#include "dictionary.h"

#include <string.h>

#include "md5.h"

int _auto_resize(struct DICTIONARY* dictionary);
int _reindex(struct DICTIONARY* dictionary, int new_capacity);
struct BUCKET* _make_bucket_array(int size);
int _get_slot(struct DICTIONARY* dictionary, char key[]);

struct DICTIONARY make_new_dict(){
    struct DICTIONARY new_dictionary;
    new_dictionary.capacity = MIN_DICT_CAPACITY;
    new_dictionary.buckets_used = 0;
    new_dictionary.buckets = _make_bucket_array(MIN_DICT_CAPACITY);
    return new_dictionary;
}

// Generates array of unused buckets. Ownership of the memory is transfered to the caller
struct BUCKET* _make_bucket_array(int size){
    struct BUCKET* buckets = malloc(size * sizeof(struct BUCKET));
    for (int i = 0; i < size; i++){buckets[i] = (struct BUCKET){.is_used = 0};}
    return buckets;
}

struct DICTIONARY make_new_populated_dict(struct BUCKET buckets[], int len){
    struct DICTIONARY new_dictionary = make_new_dict();
    populate_dict(&new_dictionary, buckets, len);
    return new_dictionary;
}

void populate_dict(struct DICTIONARY *dictionaryp, struct BUCKET buckets[], int len){
    for (int i = 0; i < len; i++) {insert_bucket(dictionaryp, &buckets[i]);}
}

// Make an unused bucket initializing its key, hash and value
struct BUCKET make_new_bucket(char key[], void* valuep) {
    struct BUCKET new_bucket;
    new_bucket.is_used = 0;
    strncpy(new_bucket.key, key, KEY_SIGNIFICANT_CHAR);
    memcpy(new_bucket.key_hash, md5_digest_str(key).data, sizeof(new_bucket.key_hash));
    new_bucket.valuep = valuep;
}

// Checks if more than half of the dictionaries buckets are used and in case they are, tries a resizing
// Returns 0 if no resize as necessary, returns 1 if an upscale was performed
int _auto_resize(struct DICTIONARY* dictionary) {
    // If there's enough capacity
    if (dictionary->buckets_used <= dictionary->capacity/2) {return 0;}

    // Upscaling
    _reindex(dictionary, dictionary->capacity<<1);
}

// Reindexes the buckets. The capacity can be increased or decreased by specifying `new_capacity`
// Returns 0 if the reindexing was sucessful. Returns -1 if the new_capacity is too low
int _reindex(struct DICTIONARY* dictionary, int new_capacity) {
    if(new_capacity<dictionary->buckets_used || new_capacity<MIN_DICT_CAPACITY){return -1;}
    // TODO IMPLEMENT REINDEXING
    return -1;
    struct BUCKET* old_buckets = dictionary->buckets;
    int old_capacity = dictionary->capacity;
    dictionary->capacity = old_capacity<<1;
    dictionary->buckets = _make_bucket_array(old_capacity<<1); // double the capacity
}

// COpies the contents of 'src_bucket' into the appropate bucket in the dictionary
// Resizes the dictionary if needed
// Returns 0 if inserted, 1 if overwritten and -1 if anything failed
int insert_bucket(struct DICTIONARY* dictionary, struct BUCKET *src_bucket){
    // Insert the bucket into its corresponding slot
    int slot = _get_slot(dictionary, src_bucket->key);
    int was_used = dictionary->buckets[slot].is_used;
    memcpy(&(dictionary->buckets[slot]), src_bucket, sizeof(struct BUCKET));

    // Update the dictionary's attributes
    dictionary->buckets[slot].is_used = 1;
    dictionary->buckets_used++;
    _auto_resize(dictionary);
    return was_used;
}

//Automatically create a bucket and insert it into the dictionary
// Returns 0 if inserted returns -1 if anything failed
int insert_value(struct DICTIONARY* dictionary, char key[], void* valuep){
    struct BUCKET new_bucket = make_new_bucket(key, valuep);
    return insert_bucket(dictionary, &new_bucket);
}

struct BUCKET* get_bucket(struct DICTIONARY* dictionary, char key[]){
    return dictionary->buckets+_get_slot(dictionary, key);
}

void* get_value(struct DICTIONARY* dictionary, char key[]){
    return get_bucket(dictionary, key)->valuep;
}

// Returns the slot of the bucket that corresponds to a key
int _get_slot(struct DICTIONARY* dictionary, char key[]) {
    // TODO IMPLEMENT SLOT GETTING
}

int is_key(struct DICTIONARY* dictionary, char key[]){
    return dictionary->buckets[_get_slot(dictionary, key)].is_used;
}