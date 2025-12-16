#include "pixels.h"
#include "hat_utils.h"

// static const uint32_t colorPallette[] = {0xFF585E, 0xFFCA3a, 0x8AC936, 0x1982C4, 0x6A4C93, 0x5432FF, 0xFF8A14, 0x00BBFF};
static const uint32_t colorPallette[] = {0xFF0000, 0xFF8800, 0xFF0088, 0x00FF00, 0x88FF00, 0x00FF88, 0x0000FF, 0x8800FF, 0x0088FF};

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
            uint32_t color = colorPallette[rand() % 9];
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