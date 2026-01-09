#include "hat_utils.h"
#include "stdio.h"
#include "string.h"

// #define INTERP_INTERMEDIATE(value, rowlen) (((value * (rowlen + 1)) + (FULL_ROW_LEN >> 1)) / (FULL_ROW_LEN + 1)) % rowlen
#define INTERP(value, rowlen) ((((value * (2 * rowlen + 1)) + FULL_ROW_LEN) / (2 * (FULL_ROW_LEN + 1))) % rowlen)
// #define INTERP_DOWN(value, rowlen) ((((value * rowlen) + FULL_ROW_LEN) / FULL_ROW_LEN) % rowlen)

uint32_t get_pixel_offset_pixel_for_row(uint32_t row, uint32_t col)
{
    if (row == 9)
    {
        return N_LEDS - ROW_9_END + INTERP(col, ROW_9_LEN);
    }
    if (row == 8)
    {
        return N_LEDS - ROW_8_END + INTERP(col, ROW_8_LEN);
    }
    if (row == 7)
    {
        return N_LEDS - ROW_7_END + INTERP(col, ROW_7_LEN);
    }
    else
    {
        return N_LEDS - ROW_WIDTH - ((row)*ROW_WIDTH) + col;
    }
}

void write_pixel(uint32_t *buffer, uint32_t col, uint32_t row, uint32_t val)
{
    uint32_t index = get_pixel_offset_pixel_for_row(row, col);
    // printf("%lu, %lu: %lu\n", row, col, index);

    buffer[index] = val;
}

void blank_buffer(uint32_t *buffer)
{
    memset(buffer, 0, sizeof(uint32_t) * N_LEDS);
}