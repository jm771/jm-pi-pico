#include "band_controler.h"
#include "pico/stdlib.h"
#include "pwm.h"

static uint redSm;
static uint greenSm;
static uint blueSm;

void band_controller_init(band_settings_t *settings)
{
    // gpio_init(19);
    // gpio_set_dir(19, GPIO_OUT);
    // gpio_init(20);
    // gpio_set_dir(20, GPIO_OUT);
    // gpio_init(21);
    // gpio_set_dir(21, GPIO_OUT);

    redSm = pwm_init(20);
    greenSm = pwm_init(21);
    // blueSm = pwm_init(19);
    blueSm = pwm_init(17);

    settings->blue = 0;
    settings->red = 0;
    settings->green = 0;
}

void band_controller_poll(band_settings_t const *settings)
{

    pwm_set_level(redSm, settings->red);
    pwm_set_level(greenSm, settings->green);
    pwm_set_level(blueSm, settings->blue);
    // gpio_put(20, 1);

    // if (settings->red)
    // {
    //     gpio_put(20, 1); // Red - working
    // }
    // else
    // {
    //     gpio_put(20, 0); // Red - working
    // }
}