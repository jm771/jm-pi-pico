#ifndef ONBOARD_LED_H
#define ONBOARD_LED_H

#include "pico/types.h"

void onboard_led_init();
void set_onboard_led(bool on);

#endif