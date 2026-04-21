#ifndef GRADIENT_FLOW_H
#define GRADIENT_FLOW_H

#include "stdint.h"
#include "band_controler.h"

void gradient_flow_produce_output(uint32_t frame, uint32_t *buffer, band_settings_t* band);

#endif