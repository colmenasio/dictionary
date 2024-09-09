#include <stdio.h>
#include "md5.h"

#define _op(A, B, C, D, k, s, i, aux_func) _operation(&A, &B, &C, &D, k, s, i, aux_func, buffer, total_buff_len)

uint32_t _F(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _G(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _H(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _I(uint32_t X, uint32_t Y, uint32_t Z);
uint8_t get_byte(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);
uint32_t get_word(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);
void _operation(uint32_t * A, uint32_t * B,uint32_t * C, uint32_t * D, uint32_t k, uint32_t s, uint32_t i,
    uint32_t(*aux_func)(uint32_t, uint32_t, uint32_t) ,uint8_t* buffer, uint64_t total_buff_len);


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
struct __128bits *md5_digest(void* buffer, uint64_t total_buff_len) {
    // INITIAL VALUES
    uint32_t A = 0x67452301, AA = A;
    uint32_t B = 0xEFCDAB89, BB = B;
    uint32_t C = 0x98BADCFE, CC = C;
    uint32_t D = 0x10325476, DD = D;

    // For each 512 bit block (16 words) do the following operations
    int n_of_blocks = (total_buff_len/64)+(total_buff_len%64>=56)+1;
    for (int block_n=0;block_n<n_of_blocks;block_n++) {
        // TODO COPY BLOCK TO A TEMPORAL BUFFER TO AVOID EXTRA CALLS TO _get_word()
        // Round 1
        _op(A, B, C, D, 0, 7, 1, _F); _op(D, A, B, C, 1, 12, 2, _F); _op(C, D, A, B, 2, 17, 3, _F); _op(B, C, D, A, 3, 22, 4, _F);
        _op(A, B, C, D, 4, 7, 5, _F); _op(D, A, B, C, 5, 12, 6, _F); _op(C, D, A, B, 6, 17, 7, _F); _op(B, C, D, A, 7, 22, 8, _F);
        _op(A, B, C, D, 8, 7, 9, _F); _op(D, A, B, C, 9, 12, 10, _F); _op(C, D, A, B, 10, 17, 11, _F); _op(B, C, D, A, 11, 22, 12, _F);
        _op(A, B, C, D, 12, 7, 13, _F); _op(D, A, B, C, 13, 12, 14, _F); _op(C, D, A, B, 14, 17, 15, _F); _op(B, C, D, A, 15, 22, 16, _F);

        // Round 2 UNIMPLEMENTED LMAOOOO (0000x0x0)
        _op(A, B, C, D, 1, 5, 17, _G); _op(D, A, B, C, 6, 9, 18, _G); _op(C, D, A, B, 11, 14, 3, _G); _op(B, C, D, A, 3, 20, 4, _G);
        _op(A, B, C, D, 5, 5, 21, _G); _op(D, A, B, C, 10, 9, 22, _G); _op(C, D, A, B, 7, 14, 7, _G); _op(B, C, D, A, 7, 20, 8, _G);
        _op(A, B, C, D, 9, 5, 25, _G); _op(D, A, B, C, 14, 9, 26, _G); _op(C, D, A, B, 3, 14, 11, _G); _op(B, C, D, A, 11, 20, 12, _G);
        _op(A, B, C, D, 13, 5, 29, _G); _op(D, A, B, C, 2, 9, 30, _G); _op(C, D, A, B, 15, 14, 15, _G); _op(B, C, D, A, 15, 20, 16, _G);

        // Round 3 UNIMPLEMENTED LMAOOOO (0000x0x0)
        _op(A, B, C, D, 0, 4, 1, _H); _op(D, A, B, C, 1, 11, 2, _H); _op(C, D, A, B, 2, 16, 3, _H); _op(B, C, D, A, 3, 23, 4, _H);
        _op(A, B, C, D, 4, 4, 5, _H); _op(D, A, B, C, 5, 11, 6, _H); _op(C, D, A, B, 6, 16, 7, _H); _op(B, C, D, A, 7, 23, 8, _H);
        _op(A, B, C, D, 8, 4, 9, _H); _op(D, A, B, C, 9, 11, 10, _H); _op(C, D, A, B, 10, 16, 11, _H); _op(B, C, D, A, 11, 23, 12, _H);
        _op(A, B, C, D, 12, 4, 13, _H); _op(D, A, B, C, 13, 11, 14, _H); _op(C, D, A, B, 14, 16, 15, _H); _op(B, C, D, A, 15, 23, 16, _H);

        // Round 4 UNIMPLEMENTED LMAOOOO (0000x0x0)
        _op(A, B, C, D, 0, 6, 1, _I); _op(D, A, B, C, 1, 10, 2, _I); _op(C, D, A, B, 2, 15, 3, _I); _op(B, C, D, A, 3, 21, 4, _I);
        _op(A, B, C, D, 4, 6, 5, _I); _op(D, A, B, C, 5, 10, 6, _I); _op(C, D, A, B, 6, 15, 7, _I); _op(B, C, D, A, 7, 21, 8, _I);
        _op(A, B, C, D, 8, 6, 9, _I); _op(D, A, B, C, 9, 10, 10, _I); _op(C, D, A, B, 10, 15, 11, _I); _op(B, C, D, A, 11, 21, 12, _I);
        _op(A, B, C, D, 12, 6, 13, _I); _op(D, A, B, C, 13, 10, 14, _I); _op(C, D, A, B, 14, 15, 15, _I); _op(B, C, D, A, 15, 21, 16, _I);

    }
    //

}

uint8_t get_byte(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index) {
    if (byte_index < total_buff_len) {return buffer[byte_index];}
    if (byte_index % 64 < 56 || (total_buff_len%56<8 && byte_index-total_buff_len<8)) {return 0x80 * (byte_index == total_buff_len);}
    if (byte_index % 64 < 64) {return ((char*)&total_buff_len)[63 - (byte_index % 64)];}
    return 0;
}

uint32_t get_word(uint8_t* buffer, uint64_t total_buff_len, uint64_t word_index) {
    uint32_t result1 = get_byte(buffer, total_buff_len, word_index*4);
    uint32_t result2 = get_byte(buffer, total_buff_len, word_index*4+1);
    uint32_t result3 = get_byte(buffer, total_buff_len, word_index*4+2);
    uint32_t result4 = get_byte(buffer, total_buff_len, word_index*4+3);
    return (result1 << 24) | (result2 << 16) | (result3 << 8) | result4;
    // return
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index) << 24 |
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index+1) << 16 |
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index+2) << 8 |
    //     (uint32_t)get_byte(buffer, total_buff_len, 4*word_index+3);
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

void _operation(uint32_t * A, uint32_t * B,uint32_t * C, uint32_t * D, uint32_t k, uint32_t s, uint32_t i, uint32_t(*aux_func)(uint32_t, uint32_t, uint32_t) ,uint8_t* buffer, uint64_t total_buff_len) {
    *A = *B + ((*A + aux_func(*B, *C, *D) + get_word(buffer, total_buff_len, k) + T[i]) << s);
}