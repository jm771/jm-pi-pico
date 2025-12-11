#include "spinning_rainbow.h"
#include "hat_utils.h"
#include "string.h"

void spinning_rainbow_produce_output(unsigned int frame, uint32_t *buffer, unsigned int nLeds)
{
    memset(buffer, 0, sizeof(uint32_t) * nLeds);

    uint32_t col = frame % ROW_WIDTH;

    for (size_t i = 0; i < N_ROWS; i++)
    {
        write_pixel(buffer, i, col, 0x0022ff);
        write_pixel(buffer, i, (col + 1) % ROW_WIDTH, 0x22ff00);
        write_pixel(buffer, i, (col + 2) % ROW_WIDTH, 0xff0022);
        write_pixel(buffer, i, (col + (ROW_WIDTH >> 1)) % ROW_WIDTH, 0x0022ff);
        write_pixel(buffer, i, (col + 1 + (ROW_WIDTH >> 1)) % ROW_WIDTH, 0x22ff00);
        write_pixel(buffer, i, (col + 2 + (ROW_WIDTH >> 1)) % ROW_WIDTH, 0xff0022);
    }
}