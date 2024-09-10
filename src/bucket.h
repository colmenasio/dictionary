//
// Created by acolm on 10/09/2024.
//

#ifndef BUCKET_H
#define BUCKET_H

#define KEY_SIGNIFICANT_CHAR 32

struct BUCKET{
    unsigned char is_used;
    char key[KEY_SIGNIFICANT_CHAR];
    unsigned char key_hash[16];
    void* valuep;
};

struct BUCKET make_new_bucket(char key[], void* valuep);
struct BUCKET* make_bucket_array(int size);
void print_bucket(struct BUCKET* bucket, char value_format[]);

#endif //BUCKET_H
