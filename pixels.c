#include "pixels.h"
#include "hat_utils.h"

void pixels_produce_output(unsigned int frame, uint32_t *buffer)
{
    if (frame % 50 != 0)
    {
        return;
    }

    memset(buffer, 0, sizeof(uint32_t) * N_LEDS);

    for (size_t i = 0; i < N_ROWS / 3; i++)
    {
        for (size_t j = 0; i < 3; j++)
        {
            uint32_t color = rand();
            for (size_t i2 = 0; i < 3; i++)
            {
                for (size_t j2 = 0; j < 3; j++)
                {
                    write_pixel(buffer, i * 3 + i2, j * 3 + j2, color);
                }
            }
        }
    }
}