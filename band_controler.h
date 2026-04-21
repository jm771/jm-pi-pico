#ifndef BAND_CONTROLLER_H
#define BAND_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t pink;
    uint8_t brightness;
    bool enabled;

} band_settings_t;

void band_controller_init(band_settings_t *);
void band_controller_poll(band_settings_t const *);
void set_color(band_settings_t * settings, uint8_t colorNo, uint8_t level);

#endif