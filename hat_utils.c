#include "hat_utils.h"
#include "stdio.h"

#define N_LEDS 200
#define N_FULL_ROWS 7
#define FULL_ROW_LEN 21
#define ROW_7_LEN 16
#define ROW_8_LEN 11
#define ROW_9_LEN 6

#define ROW_7_OFFSET (N_FULL_ROWS * FULL_ROW_LEN)
#define ROW_8_OFFSET (ROW_7_OFFSET + ROW_7_LEN)
#define ROW_9_OFFSET (ROW_8_OFFSET + ROW_8_LEN)

#define INTERP(value, rowlen) (((value * rowlen) + (FULL_ROW_LEN >> 1)) / FULL_ROW_LEN)

uint32_t get_pixel_offset_pixel_for_row(uint32_t row, uint32_t col)
{
    if (row == 9)
    {
        return ROW_9_OFFSET + INTERP(col, ROW_9_LEN);
    }
    if (row == 8)
    {
        return ROW_8_OFFSET + INTERP(col, ROW_8_LEN);
    }
    if (row == 7)
    {
        return ROW_7_OFFSET + INTERP(col, ROW_7_LEN);
    }
    else
    {
        return (row * ROW_WIDTH) + col;
    }
}

void write_pixel(uint32_t *buffer, uint32_t row, uint32_t col, uint32_t val)
{
    uint32_t index = N_LEDS - 1 - get_pixel_offset_pixel_for_row(row, col);
    printf("%lu, %lu: %lu", row, col, index);

    // printf("%lu\n", index);

    buffer[index] = val;
}
