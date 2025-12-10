#include <stdint.h>
#include "joystick.h"
#include "ws2812_utils.h"

void joystick_prog_produce_output(unsigned int frame, uint32_t *buffer, uint32_t nLeds);