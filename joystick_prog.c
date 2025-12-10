
#include "joystick_prog.h"
#include <stdlib.h>
#include <stdio.h>

#define INC 5
#define PARTY_INC 10

void joystick_prog_produce_output(unsigned int frame, uint32_t *buffer, unsigned int nLeds)
{
    static int l = 0;
    static int u = 0;

    enum dir_e joystick_pos = get_joystick_pos();

    if (joystick_pos & UP)
    {
        u = (nLeds - u) < PARTY_INC ? nLeds : u + PARTY_INC;
    }
    if (joystick_pos & DOWN)
    {
        u = (u < PARTY_INC) ? 0 : u - PARTY_INC;
    }
    if (joystick_pos & LEFT)
    {
        l = (l + INC) & 0xff;
    }
    if (joystick_pos & RIGHT)
    {
        l = (l - INC) & 0xff;
    }

    printf("Joystick new %i %d %d\n", joystick_pos, u, l);
    for (int i = 0; i < nLeds; i++)
    {
        if (i < u)
            buffer[i] = rand();
        else
            buffer[i] = urgb_u32(255, l, (255 - l));
    }
}