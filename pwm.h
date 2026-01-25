#ifndef PWM_H
#define PWM_H

#include "pico/types.h"

void pwm_install_program();

uint pwm_init(uint pin);

void pwm_set_level(uint sm, uint32_t level);

#endif