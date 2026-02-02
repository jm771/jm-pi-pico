#ifndef WS2812_UTILS_h
#define WS2812_UTILS_h

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

// I don't think this actually does anyhthing...
static inline uint32_t adjustBrightness(uint32_t val, size_t shift)
{
    uint32_t m1 = 0xff >> shift;
    uint32_t mask = m1 << 16 | m1 << 8 | m1;

    return val >> shift & mask;
}

// emperically - this wants bgr0 order... which I cannot find any justification for
static inline uint32_t toWs2812Format(uint32_t pixel_rgb, size_t brightnessShift)
{
    return (((pixel_rgb & 0xFF) >> 0 >> brightnessShift) << (16 + 8)) |
           (((pixel_rgb & 0xFF00) >> 8 >> brightnessShift) << (8 + 8)) |
           (((pixel_rgb & 0xFF0000) >> 16 >> brightnessShift) << (0 + 8));
}

void set_chain(PIO pio, uint8_t sm, uint32_t *colors, size_t l);

#endif