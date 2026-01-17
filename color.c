#include "color.h"

#define COLOR_ONE 256
#define COLOR_MAX 255
#define COLOR_ONE 256
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

uint32_t f(int32_t n, int32_t h, int32_t l, int32_t a)
{
    int32_t k = ((n * COLOR_ONE) + (h * COLOR_ONE) / 30) % (12 * COLOR_ONE);
    int32_t inner_min = MIN((k - 3 * COLOR_ONE), (9 * COLOR_ONE - k));
    int32_t outer_max = MAX(MIN(inner_min, COLOR_ONE), -COLOR_ONE);
    int32_t result = l - (a * outer_max) / COLOR_ONE;
    return MIN(result / COLOR_ONE, COLOR_MAX);
}

// input: h as an angle in [0,360] and s,l in [0,256] - output: r,g,b in [0,256]
uint32_t hsl2rgb(int32_t h, int32_t s, int32_t l)
{
    uint32_t a = s * MIN(l, COLOR_ONE - l) / COLOR_ONE;

    return f(0, h, l, a) << 16 | f(8, h, l, a) << 8 | f(4, h, l, a);
}