#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "ws2812_utils.h"

// #define MAX(x, y) ((x) > (y) ? (x) : (y))

void pixels_produce_output(unsigned int frame, uint32_t *buffer);