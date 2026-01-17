#ifndef SERVER_H
#define SERVER_H

#include "band_controler.h"

void server_poll();
int server_init(uint32_t *selectedProgram, band_settings_t const *settingsRef);

#endif