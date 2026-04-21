#ifndef FROGGER_H
#define FROGGER_H
#include <stdint.h>
#include "band_controler.h"

void frogger_init();
void frogger_produce_output(uint32_t frame, uint32_t *buffer, band_settings_t* band);
void frogger_accept_keypress(char c);
#endif