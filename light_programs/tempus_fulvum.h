#ifndef TEMPUS_FULVUM_H
#define TEMPUS_FULVUM_H

#include "stdint.h"
#include "band_controler.h"

void tempus_fulvum_produce_output(uint32_t frame, uint32_t *buffer, band_settings_t* band);

#endif