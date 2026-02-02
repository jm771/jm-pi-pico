#include "frogger.h"
#include "hat_utils.h"
#include "pico/types.h"
#include "string.h"
#include <stdio.h>
// N.B. WS2812 protocol requires ~1.25us per bit, we have 24 bits per LED and 200 LEDs so that's 6ms per frame minimum
// I'm not sure what'll happen if we retrigger DMA send between frames, I suspect "tearing" of some sort.

typedef struct
{
    int32_t x;
    int32_t y;
} frog_pos_t;

typedef struct
{
    int32_t x;
    int32_t y;
    int32_t resetTimer;
    int32_t moveOnFrame;
} car_pos_t;

static bool hasLost = false;

static frog_pos_t FrogPos;
static bool hasWon;

static car_pos_t car_positions[3];

#define CAR_COLOR 0x0000FF
#define FROG_COLOR 0x00FF00
#define WIN_COLOR 0x00FF00
#define DEAD_COLOR 0xFF0000

// void WrapPos(frog_pos_t *pos)
// {
// }

// Run once on reboot
void frogger_init()
{
    FrogPos.x = 0;
    FrogPos.y = 0;
    for (int i = 0; i < 3; i++)
    {
        car_positions[i].x = i * 2 + 2;
        car_positions[i].y = N_FULL_ROWS - 1;
        car_positions[i].resetTimer = 0;
    }
    car_positions[0].moveOnFrame = 10;
    car_positions[1].moveOnFrame = 5;
    car_positions[2].moveOnFrame = 15;
    hasLost = false;
    hasWon = false;
}

void set_hat_full_color(uint32_t *buffer, uint32_t color)
{
    blank_buffer(buffer);
    for (int i = 0; i < FULL_ROW_LEN; i++)
        for (int j = 0; j < N_ROWS; j++)
            write_pixel(buffer, i, j, color);
}

// returns true if a car has hit the frog
bool car_logic(car_pos_t *car, frog_pos_t *frog, uint32_t frame, uint32_t *buffer)
{
    if (car->x == frog->x && car->y == frog->y && car->resetTimer == 0)
    {
        hasLost = true;
        return true;
    }

    if (car->resetTimer > 0)
    {
        car->resetTimer--;
    }
    else
    {
        if (frame % car->moveOnFrame == 0)
        {
            car->y--;
        }

        if (car->y >= 0)
        {
            write_pixel(buffer, car->x, car->y, CAR_COLOR);
        }
        else
        {
            car->y = N_FULL_ROWS - 1;
            car->resetTimer = 100;
        }
    }

    printf("%li %li\n", car->y, car->resetTimer);

    return false;
}

// This is the "render" call currently called every 20ms in main (20ms > 6ms so should be fine) (nextFrameTime = currTime + 20 * 1000;)
void frogger_produce_output(uint32_t frame, uint32_t *buffer)
{
    if (hasLost)
    {
        set_hat_full_color(buffer, DEAD_COLOR);
        return;
    }

    blank_buffer(buffer);

    if (hasWon)
    {
        set_hat_full_color(buffer, WIN_COLOR);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (car_logic(&car_positions[i], &FrogPos, frame, buffer))
            {
                set_hat_full_color(buffer, DEAD_COLOR);
                return;
            }
        }

        // This API lets you "write" on a 21x10 grid - and for higher rows interpolates to find the nearest actual LED
        // So our current frog controls are argubally bad (on higher rows left / right won't actually cause movement)
        write_pixel(buffer, FrogPos.x, FrogPos.y, FROG_COLOR);

        // victory zone
        for (int i = 0; i < N_FULL_ROWS; i++)
        {
            write_pixel(buffer, FULL_ROW_LEN - 1, i, WIN_COLOR);
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
