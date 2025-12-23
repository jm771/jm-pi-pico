#ifndef HAT_UTILS_H
#define HAT_UTILS_H

#include <stdint.h>
#define ROW_WIDTH 21
#define N_ROWS 10

#define N_LEDS 200
#define N_FULL_ROWS 7
#define FULL_ROW_LEN 21
// #define ROW_6_LEN 22
#define ROW_7_LEN 16
#define ROW_8_LEN 11
#define ROW_9_LEN 6

// #define ROW_6_OFFSET (N_FULL_ROWS * FULL_ROW_LEN)
// #define ROW_7_OFFSET (ROW_6_OFFSET + ROW_6_LEN)
#define ROW_6_END (N_FULL_ROWS * FULL_ROW_LEN)
#define ROW_7_END (ROW_6_END + ROW_7_LEN)
#define ROW_8_END (ROW_7_END + ROW_8_LEN)
#define ROW_9_END (ROW_8_END + ROW_9_LEN)
#define VALID_LED_START N_LEDS - ROW_9_END

void write_pixel(uint32_t *buffer, uint32_t col, uint32_t row, uint32_t val);
void blank_buffer(uint32_t *buffer);

#endif