#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>

// input: h as an angle in [0,360] and s,l in [0,256] - output: r,g,b in [0,256]
uint32_t hsl2rgb(int32_t h, int32_t s, int32_t l);

#endif