#include <stdio.h>
#include "md5.h"

#include <string.h>

#define _op(A, B, C, D, k, s, i, aux_func) _operation(&A, &B, &C, &D, k, s, i-1, aux_func, X)

uint8_t get_byte(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);
uint32_t get_word(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);
void fill_block(uint32_t* word_buff, uint8_t* og_buffer, uint64_t og_buff_len, uint32_t block_n);
uint32_t _F(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _G(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _H(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _I(uint32_t X, uint32_t Y, uint32_t Z);
void _operation(uint32_t * A, uint32_t * B,uint32_t * C, uint32_t * D, uint32_t k, uint32_t s, uint32_t i,
    uint32_t(*aux_func)(uint32_t, uint32_t, uint32_t) ,uint32_t* curr_block);


static const uint32_t T[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

// buffer is a pointer to the start ot the message to be digested
// byte_len is the length in bytes of said message
struct hash128 md5_digest(void* buffer, uint64_t total_buff_len) {
    // INITIAL VALUES
    uint32_t A = 0x67452301, AA;
    uint32_t B = 0xEFCDAB89, BB;
    uint32_t C = 0x98BADCFE, CC;
    uint32_t D = 0x10325476, DD;

    uint32_t X[16];

    // For each 512 bit block (16 words) do the following operations
    int n_of_blocks = (total_buff_len/64)+(total_buff_len%64>=56)+1;
    for (int block_n=0;block_n<n_of_blocks;block_n++) {
        // Initialize registers adn fill block buffer
        AA = A; BB = B; CC = C; DD = D;
        fill_block(X, buffer, total_buff_len, block_n);

        // Round 1
        _op(A, B, C, D, 0, 7, 1, _F); _op(D, A, B, C, 1, 12, 2, _F); _op(C, D, A, B, 2, 17, 3, _F); _op(B, C, D, A, 3, 22, 4, _F);
        _op(A, B, C, D, 4, 7, 5, _F); _op(D, A, B, C, 5, 12, 6, _F); _op(C, D, A, B, 6, 17, 7, _F); _op(B, C, D, A, 7, 22, 8, _F);
        _op(A, B, C, D, 8, 7, 9, _F); _op(D, A, B, C, 9, 12, 10, _F); _op(C, D, A, B, 10, 17, 11, _F); _op(B, C, D, A, 11, 22, 12, _F);
        _op(A, B, C, D, 12, 7, 13, _F); _op(D, A, B, C, 13, 12, 14, _F); _op(C, D, A, B, 14, 17, 15, _F); _op(B, C, D, A, 15, 22, 16, _F);

        // Round 2
        _op(A, B, C, D, 1, 5, 17, _G); _op(D, A, B, C, 6, 9, 18, _G); _op(C, D, A, B, 11, 14, 19, _G); _op(B, C, D, A, 0, 20, 20, _G);
        _op(A, B, C, D, 5, 5, 21, _G); _op(D, A, B, C, 10, 9, 22, _G); _op(C, D, A, B, 15, 14, 23, _G); _op(B, C, D, A, 4, 20, 24, _G);
        _op(A, B, C, D, 9, 5, 25, _G); _op(D, A, B, C, 14, 9, 26, _G); _op(C, D, A, B, 3, 14, 27, _G); _op(B, C, D, A, 8, 20, 28, _G);
        _op(A, B, C, D, 13, 5, 29, _G); _op(D, A, B, C, 2, 9, 30, _G); _op(C, D, A, B, 7, 14, 31, _G); _op(B, C, D, A, 12, 20, 32, _G);

        // Round 3
        _op(A, B, C, D, 5, 4, 33, _H); _op(D, A, B, C, 8, 11, 34, _H); _op(C, D, A, B, 11, 16, 35, _H); _op(B, C, D, A, 14, 23, 36, _H);
        _op(A, B, C, D, 1, 4, 37, _H); _op(D, A, B, C, 4, 11, 38, _H); _op(C, D, A, B, 7, 16, 39, _H); _op(B, C, D, A, 10, 23, 40, _H);
        _op(A, B, C, D, 13, 4, 41, _H); _op(D, A, B, C, 0, 11, 42, _H); _op(C, D, A, B, 3, 16, 43, _H); _op(B, C, D, A, 6, 23, 44, _H);
        _op(A, B, C, D, 9, 4, 45, _H); _op(D, A, B, C, 12, 11, 46, _H); _op(C, D, A, B, 15, 16, 47, _H); _op(B, C, D, A, 2, 23, 48, _H);

        // Round 4
        _op(A, B, C, D, 0, 6, 49, _I); _op(D, A, B, C, 7, 10, 50, _I); _op(C, D, A, B, 14, 15, 51, _I); _op(B, C, D, A, 5, 21, 52, _I);
        _op(A, B, C, D, 12, 6, 53, _I); _op(D, A, B, C, 3, 10, 54, _I); _op(C, D, A, B, 10, 15, 55, _I); _op(B, C, D, A, 1, 21, 56, _I);
        _op(A, B, C, D, 8, 6, 57, _I); _op(D, A, B, C, 15, 10, 58, _I); _op(C, D, A, B, 6, 15, 59, _I); _op(B, C, D, A, 13, 21, 60, _I);
        _op(A, B, C, D, 4, 6, 61, _I); _op(D, A, B, C, 11, 10, 62, _I); _op(C, D, A, B, 2, 15, 63, _I); _op(B, C, D, A, 9, 21, 64, _I);

        // Update the registers
        A += AA; B += BB; C += CC; D += DD;
    }

    struct hash128 result = {.data = {A, B, C, D}};
    return result;
}

// Digests a string, including the `\0` character
struct hash128 md5_digest_str(char* str) {
    return md5_digest(str, strlen(str));
}

uint8_t get_byte(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index) {
    if (byte_index < total_buff_len) {return buffer[byte_index];}
    if (byte_index % 64 < 56 || (total_buff_len%56<8 && byte_index-total_buff_len<8)) {return 0x80 * (byte_index == total_buff_len);}
    uint64_t len_bits = 8*total_buff_len;
    if (byte_index % 64 < 64) {return ((char*)&len_bits)[byte_index%64 - 56];}
    return 0;
}

uint32_t get_word(uint8_t* buffer, uint64_t total_buff_len, uint64_t word_index) {
    uint32_t result1 = get_byte(buffer, total_buff_len, word_index*4);
    uint32_t result2 = get_byte(buffer, total_buff_len, word_index*4+1);
    uint32_t result3 = get_byte(buffer, total_buff_len, word_index*4+2);
    uint32_t result4 = get_byte(buffer, total_buff_len, word_index*4+3);
    return result1 | (result2 << 8) | (result3 << 16) | result4 << 24;
    // return
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index) |
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index+1) << 8 |
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index+2) << 16 |
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index+3) << 24;
}


void fill_block(uint32_t* word_buff, uint8_t* og_buffer, uint64_t og_buff_len, uint32_t block_n) {
    for (int i = 0; i < 16; i++) {word_buff[i] = get_word(og_buffer, og_buff_len, 16*block_n+i);};
}

uint32_t _F(uint32_t X, uint32_t Y, uint32_t Z) {
    return (X & Y) | (~X & Z);
}

uint32_t _G(uint32_t X, uint32_t Y, uint32_t Z) {
    return (X & Z) | (Y & ~Z);
}

uint32_t _H(uint32_t X, uint32_t Y, uint32_t Z) {
    return X ^ Y ^ Z;
}

uint32_t _I(uint32_t X, uint32_t Y, uint32_t Z) {
    return Y ^ (X | ~Z);
}

void _operation(uint32_t * A, uint32_t * B,uint32_t * C, uint32_t * D, uint32_t k, uint32_t s, uint32_t i,
    uint32_t(*aux_func)(uint32_t, uint32_t, uint32_t) ,uint32_t* curr_block) {
    uint32_t binding = *A + aux_func(*B, *C, *D) + curr_block[k] + T[i];
    *A = *B + ((binding << s) | (binding >> (32-s)));
}

void print_hash128(struct hash128* hash) {
    for (int i = 0; i<16;i++){printf("%02x", ((unsigned char*)hash->data)[i]);}
}