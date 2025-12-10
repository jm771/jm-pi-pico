#ifndef HAT_UTILS_H
#define HAT_UTILS_H

#include <stdint.h>
#define ROW_WIDTH 21
#define N_ROWS 10

void write_pixel(uint32_t *buffer, uint32_t row, uint32_t col, uint32_t val);

#endif