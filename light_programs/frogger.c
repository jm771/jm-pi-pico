#include "frogger.h"
#include "hat_utils.h"
#include "pico/types.h"
#include "string.h"
// N.B. WS2812 protocol requires ~1.25us per bit, we have 24 bits per LED and 200 LEDs so that's 6ms per frame minimum
// I'm not sure what'll happen if we retrigger DMA send between frames, I suspect "tearing" of some sort.

typedef struct
{
    int32_t x;
    int32_t y;
} frog_pos_t;

static frog_pos_t FrogPos;
static frog_pos_t Car1Pos;
static frog_pos_t Car2Pos;
static frog_pos_t Car3Pos;
static bool hasWon;

// void WrapPos(frog_pos_t *pos)
// {
// }

// Run once on reboot
void frogger_init()
{
    FrogPos.x = 0;
    FrogPos.y = 0;
}

// This is the "render" call currently called every 20ms in main (20ms > 6ms so should be fine) (nextFrameTime = currTime + 20 * 1000;)
void frogger_produce_output(uint32_t frame, uint32_t *buffer)
{
    blank_buffer(buffer);

    if (hasWon) {
        memset(buffer, 0xFF, sizeof(uint32_t) * N_LEDS);
    } else {
        // This API lets you "write" on a 21x10 grid - and for higher rows interpolates to find the nearest actual LED
        // So our current frog controls are argubally bad (on higher rows left / right won't actually cause movement)
        write_pixel(buffer, FrogPos.x, FrogPos.y, 0x00FF00);

        // victory zone
        for (int i = 0; i < N_FULL_ROWS; i++) {
            write_pixel(buffer, FULL_ROW_LEN - 1, i, 0x00FF00);
        }
    }
}

// n.b. main uses `r` keypress to reset the device so this won't get forwarded
// This gets called from an interupt - should do as little work as possible
void frogger_accept_keypress(char c)
{
    switch (c)
    {
    case 'w':
    {
        if (FrogPos.y < N_ROWS - 1)
        {
            FrogPos.y++;
        }
        break;
    }
    case 'a':
    {
        if (FrogPos.x > 0)
        {
            FrogPos.x--;
        }
        break;
    }
    case 's':
    {
        
        if (FrogPos.y > 0)
        {
            FrogPos.y--;
        }
        break;
    }
    case 'd':
    {
        FrogPos.x++;
        if (FrogPos.x >= FULL_ROW_LEN - 1)
        {
            hasWon = true;
        }
        break;
    }
    }
}
