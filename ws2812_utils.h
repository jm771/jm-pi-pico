#ifndef WS2818_UTILS_h
#define WS2818_UTILS_h

#include <stdio.h>
#include "hardware/pio.h"

static inline void put_pixel(PIO pio, uint8_t sm, uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) |
           ((uint32_t)(g) << 16) |
           (uint32_t)(b);
}

static inline uint32_t adjustBrightness(uint32_t val, size_t shift)
{
    return ((val & (0xff0000)) >> shift) | ((val & (0xff00)) >> shift) | ((val & (0xff)) >> shift);
}

void set_chain(PIO pio, uint8_t sm, uint32_t *colors, size_t l);

#endif