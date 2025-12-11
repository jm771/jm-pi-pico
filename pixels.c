#include "pixels.h"
#include "hat_utils.h"

void pixels_produce_output(unsigned int frame, uint32_t *buffer)
{
    if (frame % 50 != 0)
    {
        return;
    }

    memset(buffer, 0, sizeof(uint32_t) * N_LEDS);

    for (size_t i = 0; i < (ROW_WIDTH / 3); i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            uint32_t color = rand();
            for (size_t i2 = 0; i2 < 3; i2++)
            {
                for (size_t j2 = 0; j2 < 3; j2++)
                {
                    write_pixel(buffer, j * 3 + j2, i * 3 + i2, color);
                }
            }
        }
    }
}