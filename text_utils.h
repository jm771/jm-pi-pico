// uint32_t get_char_width

#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include "stdint.h"

uint32_t write_char_4pt(uint32_t *buffer, char character, uint32_t color, int32_t x, int32_t y);
uint32_t get_6pt_width(char character);
void write_char_6pt(uint32_t *buffer, char character, uint32_t color, int32_t x_off);

#endif