#ifndef BAND_CONTROLLER_H
#define BAND_CONTROLLER_H

#include <stdint.h>

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} band_settings_t;

void band_controller_init(band_settings_t *);
void band_controller_poll(band_settings_t const *);

#endif