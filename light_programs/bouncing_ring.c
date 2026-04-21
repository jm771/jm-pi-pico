#include "bouncing_ring.h"
#include "hat_utils.h"
#include "color.h"
#include <stdbool.h>

static uint32_t color;

void output_ring(uint32_t frame, uint32_t *buffer, band_settings_t* band, uint32_t divisor)
{
    bool colorChange = frame % (divisor * 2 * N_ROWS) == 0;
    frame /= divisor;

    const uint32_t Modulus = N_ROWS * 2;
    uint32_t row = frame % Modulus;

    uint32_t const hue = ((frame / N_ROWS) * 111) % 360;


    if (row > N_ROWS)
    {
        row = Modulus - row;
    }

    if (colorChange)
    {
        color += 1;
        if (color >= 3) color -=3;
        set_color(band, color, 255);
        
    }

    for (uint32_t i = 0; i < FULL_ROW_LEN; i++)
    {
        write_pixel(buffer, i, row, hsl2rgb(hue, 255, 100));
    }
}

void bouncing_ring_produce_output(uint32_t frame, uint32_t *buffer, band_settings_t* band)
{
    blank_buffer(buffer);
    output_ring(frame, buffer, band, 5);
    output_ring(frame, buffer, band, 7);
}