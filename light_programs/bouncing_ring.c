#include "bouncing_ring.h"
#include "hat_utils.h"
#include "color.h"

void bouncing_ring_produce_output(uint32_t frame, uint32_t *buffer)
{
    blank_buffer(buffer);

    const uint32_t Modulus = N_ROWS * 2;
    uint32_t row = frame % Modulus;

    static uint32_t hue = 0;
    if (row == N_ROWS + 1 || row == 0)
    {
        hue = hue + 111;
        if (hue > 360)
        {
            hue -= 360;
        }
    }

    if (row > N_ROWS)
    {
        row = Modulus - row;
    }

    for (uint32_t i = 0; i < FULL_ROW_LEN; i++)
    {
        write_pixel(buffer, i, row, hsl2rgb(hue, 160, 100));
    }
}