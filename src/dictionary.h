//
// Created by acolm on 10/09/2024.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#define KEY_SIGNIFICANT_CHAR 32
#define MIN_DICT_CAPACITY 8
#define MAX_DICT_CAPACITY 512

struct BUCKET{
  unsigned char is_used;
  char key[KEY_SIGNIFICANT_CHAR];
  char key_hash[16];
  void* valuep;
};

struct DICTIONARY{
  int capacity;
  int buckets_used;
  struct BUCKET* buckets;
};

struct DICTIONARY make_new_dict();
struct DICTIONARY make_new_populated_dict(struct BUCKET buckets[], int len);

void populate_dict(struct DICTIONARY *dictionaryp, struct BUCKET buckets[], int len);
int insert_bucket(struct DICTIONARY* dictionary, struct BUCKET *bucket);
int insert_value(struct DICTIONARY* dictionary, char key[], void* valuep);
struct BUCKET* get_bucket(struct DICTIONARY* dictionary, char key[])
void* get_value(struct DICTIONARY* dictionary, char key[]);
int is_key(struct DICTIONARY* dictionary, char key[]);

#endif //DICTIONARY_H
