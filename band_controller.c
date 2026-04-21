#include "band_controler.h"
#include "pico/stdlib.h"
#include "pwm.h"
#include <stdlib.h>

static uint redSm;
static uint greenSm;
static uint blueSm;
static uint pinkSm;

void band_controller_init(band_settings_t *settings)
{
    redSm = pwm_init(19);
    greenSm = pwm_init(20);
    blueSm = pwm_init(17);
    pinkSm = pwm_init(21);

    settings->blue = 0;
    settings->red = 0;
    settings->green = 0;
    settings->pink = 0;
    settings->brightness = 8;
}

uint32_t adjust_level(uint8_t base, uint32_t dimness, uint8_t brightness)
{
    uint32_t adj_level = ((((uint32_t)base)) << brightness) ;
    uint32_t dimmed_level = adj_level >> dimness;
    return dimmed_level;
}

void band_controler_zero(band_settings_t * settings)
{
    settings->blue = 0;
    settings->green = 0;
    settings->red = 0;
    settings->pink = 0;
}

void set_color(band_settings_t * settings, uint8_t colorNo, uint8_t level)
{
    band_controler_zero(settings);
    switch (colorNo) {
        case 0:
        settings->red = level;
        break;
        case 1:
        settings->green = level;
        break;
        case 2:
        settings->blue = level;
        break;
        case 3:
        settings->pink = level;
        break;
    }
}

void band_default_pattern(band_settings_t * bandSettings, uint32_t frame)
{
    // Do the pulsing thing
    uint32_t intensity = (50 - abs((int32_t)(frame % 100) - 49)) * 5;
    uint32_t color = (frame / 100) % 3;
    if (color == 0) {
        bandSettings->red = intensity;
    }
    if (color == 1) {
        bandSettings->green = intensity;
    }
    if (color == 2) {
        bandSettings->blue = intensity;
    }
}

void band_controller_poll(band_settings_t const *settings)
{
    pwm_set_level(redSm, adjust_level(settings->red, 0, settings->brightness));
    pwm_set_level(greenSm, adjust_level(settings->green, 3, settings->brightness));
    pwm_set_level(blueSm, adjust_level(settings->blue, 2, settings->brightness));
    pwm_set_level(pinkSm, adjust_level(settings->pink, 4, settings->brightness));
}