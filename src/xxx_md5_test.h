//
// Created by acolm on 08/09/2024.
//

#ifndef MD5_DEBUG_H
#define MD5_DEBUG_H

#include <stdint.h>

uint8_t get_byte(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);
uint32_t get_word(uint8_t* buffer, uint64_t total_buff_len, uint64_t byte_index);

#endif //MD5_DEBUG_H
