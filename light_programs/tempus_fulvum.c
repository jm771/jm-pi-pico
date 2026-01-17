#include "tempus_fulvum.h"
#include "color.h"
#include "hat_utils.h"
#include "pico/stdlib.h"

void disc(uint32_t *buffer, uint32_t radiusMin, uint32_t radiusMax, uint32_t val, uint32_t lum, bool dial)
{
    uint32_t color = hsl2rgb(val, 256, lum);

    for (uint32_t i = radiusMin; i < radiusMax; i++)
    {
        uint32_t row = N_ROWS - i;
        for (uint32_t j = 0; j < FULL_ROW_LEN; j++)
        {
            write_pixel(buffer, j, row, color);
        }
    }

    if (dial)
    {
        uint32_t row = N_ROWS - ((radiusMax + radiusMin) / 2);
        uint32_t col = (val * FULL_ROW_LEN + (FULL_ROW_LEN / 2)) / 360;
        write_pixel(buffer, col, row, 0xffffff);
    }
}

uint32_t lunar(uint32_t now)
{
    // TODO
    return 14;
    // const off = (daynum(now.getFullYear(), now.getMonth(), now.getDate()) -
    //              daynum(2000, 1, 6));
    // const phase = off % 29.53;
    // return (phase > 14.765 ? ((29.53 - phase) / 14.765) : (phase / 14.765));
}

void render(uint32_t epoc, uint32_t *buffer)
{
    uint32_t day_time = epoc % (60 * 60 * 24);
    uint32_t hour = day_time / 24;
    uint32_t minute = (day_time % 24) / 60;
    uint32_t second = day_time % (24 * 60);
    uint32_t phase = lunar(epoc);

    disc(buffer, 7, 10, minute * 6, 128, false);
    disc(buffer, 5, 7, second * 6, 128, true);
    // disc(buffer, 3, 5, second * 6, 128, true);
    disc(buffer, 3, 5, hour * 30, 128, false);
    disc(buffer, 0, 3, hour * 30, phase, false);
}

void tempus_fulvum_produce_output(uint32_t frame, uint32_t *buffer)
{
    // Time is hard...
    uint32_t epoc = (uint32_t)get_absolute_time() / 1000 / 1000;
    render(epoc, buffer);
}