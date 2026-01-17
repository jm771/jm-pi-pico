#include "bouncing_ring.h"
#include "hat_utils.h"
#include "color.h"

void output_ring(uint32_t frame, uint32_t *buffer, uint32_t divisor)
{
    frame /= divisor;

    const uint32_t Modulus = N_ROWS * 2;
    uint32_t row = frame % Modulus;

    uint32_t const hue = ((frame / N_ROWS) * 111) % 360;

    if (row > N_ROWS)
    {
        row = Modulus - row;
    }

    for (uint32_t i = 0; i < FULL_ROW_LEN; i++)
    {
        write_pixel(buffer, i, row, hsl2rgb(hue, 255, 100));
        // write_pixel(buffer, i, N_ROWS - 1 - row, hsl2rgb(hue, 255, 100));
    }
}

void bouncing_ring_produce_output(uint32_t frame, uint32_t *buffer)
{
    blank_buffer(buffer);
    output_ring(frame, buffer, 5);
    output_ring(frame, buffer, 7);
}