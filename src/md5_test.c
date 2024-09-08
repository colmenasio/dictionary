//
// Created by acolm on 08/09/2024.
//

#include <stdio.h>
#include "md5.h"
#include "md5_test.h"


static const char TEST_STR[] = "Hello Worldasdasfsefefefaefkaknfvlkmasmflakdaskdnlas";

int get_str_len(char* str);
int test_byte_getter();
int test_word_getter();

int main() {
    test_byte_getter();
    test_word_getter();
}

int get_str_len(char* str) {
    int len= 0;
    for (; str[len] != '\0'; len++);
    return len+1;
}

int test_byte_getter() {
    int len = get_str_len(TEST_STR);
    int extended_message_len = 64*((len/64)+(len%64>=56)+1);
    printf("MESSAGE LENGTH IN BYTES: %d\n", len);
    printf("PADDED MESSAGE LENGHT IN BYTES: %d\n", extended_message_len);
    for (int i = 0; i < extended_message_len; i++) {printf(i%4 == 3? "%x\n" : "%x ", get_byte(TEST_STR, len, i));}
    return 0;
}

int test_word_getter() {
    int len = get_str_len(TEST_STR);
    int total_n_of_words = 16*((len/64)+(len%64>=56)+1);
    printf("MESSAGE LENGTH IN BYTES: %d\n", len);
    printf("TOTAL N OF WORDS IN BYTES: %d\n", total_n_of_words);
    for (int i = 0; i < total_n_of_words; i++) {printf("%08x\n", get_word(TEST_STR, len, i));}
    return 0;
}