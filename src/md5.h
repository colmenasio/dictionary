//
// Created by acolm on 08/09/2024.
//

#ifndef MD5_H
#define MD5_H

#include <stdint.h>

struct __128bits{
    char data[16];
};

struct __128bits *md5_digest(void* buffer, uint64_t buff_len);

#endif //MD5_H
