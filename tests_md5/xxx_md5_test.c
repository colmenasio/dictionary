//
// Created by acolm on 08/09/2024.
//

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "md5.h"
#include "xxx_md5_test.h"




static const char TEST_STR[] = "Hola";

void test_byte_getter();
void test_word_getter();
int test_md5_algo();

int main() {
    return test_md5_algo();
}

void test_byte_getter() {
    int len = strnlen(TEST_STR, 1024);
    int extended_message_len = 64*((len/64)+(len%64>=56)+1);
    printf("MESSAGE LENGTH IN BYTES: %d\n", len);
    printf("PADDED MESSAGE LENGHT IN BYTES: %d\n", extended_message_len);
    for (int i = 0; i < extended_message_len; i++) {printf(i%4 == 3? "%x\n" : "%x ", get_byte(TEST_STR, len, i));}
    return;
}

// Manual test
void test_word_getter() {
    int len = strnlen(TEST_STR, 1024);
    int total_n_of_words = 16*((len/64)+(len%64>=56)+1);
    printf("MESSAGE LENGTH IN BYTES: %d\n", len);
    printf("TOTAL N OF WORDS IN BYTES: %d\n", total_n_of_words);
    for (int i = 0; i < total_n_of_words; i++) {printf("%08x\n", get_word(TEST_STR, len, i));}
    return;
}

// Automated test. Returns 0 if passed, 1 if failed, -1 if an error was encountered
int test_md5_algo() {
    // TEST WITH STRINGS
    char *msg1 = "HIIIIII!!", *ms2 = "This string is considerably longer to purposefully trigger multiple block procesing. Pechance.";
    struct hash128 result1 = md5_digest_str(msg1), result2 = md5_digest_str(ms2);
    struct hash128 exp_result_1 = {.data = {0x20ea6fcf, 0xcedc5303, 0xae62521c, 0x55b884aa}};
    struct hash128 exp_result_2 = {.data = {0xd9931ce1, 0x5d485c24, 0x8a69927c, 0x14c6e469}};
    int test_1_result = memcmp(&result1, &exp_result_1, 16);
    int test_2_result = memcmp(&result2, &exp_result_2, 16);
    printf("HASH 1: "); print_hash128(&result1); printf(test_1_result? "->FAIL\n":"->OK\n");
    printf("HASH 2: "); print_hash128(&result2); printf(test_2_result? "->FAIL\n":"->OK\n");

    //TEST WITH A WHOLE FILE LMAOO
    // Open the file
    HANDLE hFile = CreateFile("tests_md5/funny_test.jpg", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to open file. Error code: %lu\n", GetLastError());
        return -1;
    }

    // Get the file size
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        printf("Failed to get file size. Error code: %lu\n", GetLastError());
        CloseHandle(hFile);
        return -1;
    }

    // Create a file mapping object
    HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL) {
        printf("Failed to create file mapping. Error code: %lu\n", GetLastError());
        CloseHandle(hFile);
        return -1;
    }

    // Map the file into the process's address space
    void* fileData = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (fileData == NULL) {
        printf("Failed to map view of file. Error code: %lu\n", GetLastError());
        CloseHandle(hMapping);
        CloseHandle(hFile);
        return -1;
    }

    // Close the file and mapping handle since the mapping is already in memory
    CloseHandle(hMapping);
    CloseHandle(hFile);

    struct hash128 result3 = md5_digest(fileData, fileSize.QuadPart);
    struct hash128 exp_result_3 = {.data = {0xcffaad2f, 0x519182e0, 0x90dcd870, 0x17fa68ac}};
    int test_3_result = memcmp(&result3, &exp_result_3, 16);
    printf("HASH 3: "); print_hash128(&result3); printf(test_3_result? "->FAIL\n":"->OK\n");


    // Unmap the file from memory
    if (!UnmapViewOfFile(fileData)) {
        printf("Failed to unmap view of file. Error code: %lu\n", GetLastError());
        return -1;
    }

    return test_1_result || test_2_result || test_3_result;
}