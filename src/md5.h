//
// Created by acolm on 08/09/2024.
//

#ifndef MD5_H
#define MD5_H

#include <stdint.h>

struct hash128{
    uint32_t data[4];
};

struct hash128 md5_digest(void* buffer, uint64_t buff_len);
struct hash128 md5_digest_str(char* str);

void print_hash128(struct hash128* hash);

#endif //MD5_H
