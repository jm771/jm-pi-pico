#include "gradient_flow.h"
#include "color.h"
#include "hat_utils.h"
#include <stdio.h>

void gradient_flow_produce_output(uint32_t frame, uint32_t *buffer)
{
    blank_buffer(buffer);

    for (uint32_t i = 0; i < N_ROWS; i++)
    {
        for (uint32_t j = 0; j < FULL_ROW_LEN; j++)
        {
            uint32_t val = hsl2rgb((i * 2 * N_ROWS + j * 2 + frame) % 360, 256, 128);
            printf("%lx\n", val);
            write_pixel(buffer, j, i, val);
        }
    }
}