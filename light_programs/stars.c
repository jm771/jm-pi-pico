#include "stars.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "ws2812_utils.h"

#define RAMP_TIME 20
#define PERIOD 100
// #define MAX(x, y) ((x) > (y) ? (x) : (y))

void stars_produce_output(uint32_t frame, uint32_t *buffer, band_settings_t* band)
{
    static uint32_t colour = 0;
    static uint32_t seed = 0;

    if (frame % PERIOD == RAMP_TIME)
    {
        memset(buffer, 0, sizeof(uint32_t) * N_LEDS);
        colour = rand();
        seed = rand();
    }
    else
    {
        int32_t dist_from_min = abs((int32_t)(frame % PERIOD) - RAMP_TIME);
        int32_t scale_down = MAX(RAMP_TIME - dist_from_min, 0);

        snap_color(band, colour, 255 >> (scale_down / 2));

        srand(seed);
        for (size_t i = VALID_LED_START; i < N_LEDS; i++)
        {
            if (rand() < RAND_MAX / 4)
            {
                buffer[i] = adjustBrightness(colour, scale_down / 2);
            }
        }
    }
}