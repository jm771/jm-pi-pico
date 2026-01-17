#ifndef MAIN_LED_DRIVER_H
#define MAIN_LED_DRIVER_H

#include <stdint.h>

#define N_PROGS 7
#define STARTING_PROGRAM 1

const char **GetProgramNames();

void main_led_init();
void main_led_blank();
void main_led_poll(uint32_t frame, uint32_t program_number);

#endif