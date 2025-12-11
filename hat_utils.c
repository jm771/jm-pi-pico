#include "hat_utils.h"
#include "stdio.h"

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
