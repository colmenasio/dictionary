#include <stdio.h>
#include "md5.h"

uint32_t _F(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _G(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _H(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t _I(uint32_t X, uint32_t Y, uint32_t Z);
uint8_t get_byte(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);
uint32_t get_word(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);

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
struct __128bits *md5_digest(void* buffer, uint64_t buff_len) {
    // INITIAL VALUES
    uint32_t A = 0x67452301;
    uint32_t B = 0xEFCDAB89;
    uint32_t C = 0x98BADCFE;
    uint32_t D = 0x10325476;


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