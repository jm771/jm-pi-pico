#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "ws2812_utils.h"
#include "band_controler.h"

void pixels_produce_output(uint32_t frame, uint32_t *buffer, band_settings_t* band);