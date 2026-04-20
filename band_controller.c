#include "band_controler.h"
#include "pico/stdlib.h"
#include "pwm.h"

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
}

uint32_t adjust_level(uint8_t base, uint32_t dimness)
{
    uint32_t adj_level = ((((uint32_t)base)) << 8) ;
    uint32_t dimmed_level = adj_level >> dimness;
    return dimmed_level;
}

void band_controller_poll(band_settings_t const *settings)
{
    pwm_set_level(redSm, adjust_level(settings->red, 0));
    pwm_set_level(greenSm, adjust_level(settings->green, 3));
    pwm_set_level(blueSm, adjust_level(settings->blue, 2));
    pwm_set_level(pinkSm, adjust_level(settings->pink, 3));
}