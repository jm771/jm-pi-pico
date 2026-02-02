#include "frogger.h"
#include "hat_utils.h"
#include "pico/types.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "game_state.h"
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

static game_state_t GameState;
static frog_pos_t FrogPos;

#define NUM_CARS 8
#define CAR_COLOR 0x0000FF
#define FROG_COLOR 0x00FF00
#define WIN_COLOR 0x00FF00
#define DEAD_COLOR 0xFF0000
#define FROG_SPRITE_X 11
#define FROG_SPRITE_Y 7

static car_pos_t car_positions[NUM_CARS];

static uint32_t frog_sprite[FROG_SPRITE_X][FROG_SPRITE_Y];

// Run once on reboot
void frogger_init()
{
    game_state_init(&GameState);
    FrogPos.x = 0;
    FrogPos.y = 0;
    for (int i = 0; i < NUM_CARS; i++)
    {
        car_positions[i].x = i * 2 + 2;
        car_positions[i].y = N_FULL_ROWS - 1;
        car_positions[i].resetTimer = 0;
    }
    car_positions[0].moveOnFrame = 10;
    for (int i = 1; i < NUM_CARS; i++)
    {
        int increment = rand() % 3;
        if (i % 2 == 0)
        {
            car_positions[i].moveOnFrame = 18 - increment;
        }
        else
        {
            car_positions[i].moveOnFrame = 5 + increment;
        }
    }
}

void display_splat(uint32_t *buffer, frog_pos_t *frog, uint32_t animationFrame)
{
    blank_buffer(buffer);
    if (animationFrame > 0 && animationFrame < 5)
    {
        write_pixel(buffer, frog->x + animationFrame, frog->y, DEAD_COLOR);
        write_pixel(buffer, frog->x, frog->y + animationFrame, DEAD_COLOR);
        write_pixel(buffer, frog->x - animationFrame, frog->y, DEAD_COLOR);
        write_pixel(buffer, frog->x, frog->y - animationFrame, DEAD_COLOR);
    }
}

void render_sprite(uint32_t* buffer)
{
    for (int x = 0; x < FROG_SPRITE_X; x++) {
        for (int y = 0; y < FROG_SPRITE_Y; y++) {
            int x_coord = x - 9; // move the sprite to the right so the non-hat wearer can see it
            if (x_coord < 0) {
                x_coord += FULL_ROW_LEN;
            }
            write_pixel(buffer, x_coord, y, frog_sprite[x][y]);
        }
    }
}

void fill_frog_sprite()
{
    // hind legs
    for (int x = 0; x < 1; x++)
        for (int y = 0; y < N_FULL_ROWS; y++)
            frog_sprite[x][y] = 0x00FF00;
    // body
    for (int x = 1; x < 3; x++)
        for (int y = 1; y < N_FULL_ROWS - 1; y++)
            frog_sprite[x][y] = 0x00FF00;
    // head
    for (int x = 3; x < 6; x++)
        for (int y = 2; y < N_FULL_ROWS - 2; y++)
            frog_sprite[x][y] = 0x00FF00;
    frog_sprite[4][2] = 0xFFFFFF;
    frog_sprite[4][N_FULL_ROWS - 2] = 0xFFFFFF;
}


void display_victory(uint32_t* buffer, int32_t animationFrame)
{
    blank_buffer(buffer);
    if (animationFrame > 0) {
        fill_frog_sprite();
        int tongueLength = animationFrame >= 5 ? 4 : animationFrame;
        // stick out the frog's tongue
        for (int x = 6; x < 6 + tongueLength; x++) {
            frog_sprite[x][3] = 0xFF0000;
        }
        render_sprite(buffer);
    }
}

void set_hat_full_color(uint32_t* buffer, uint32_t color)
{
    blank_buffer(buffer);
    for (int i = 0; i < FULL_ROW_LEN; i++)
        for (int j = 0; j < N_ROWS; j++)
            write_pixel(buffer, i, j, color);
}

void car_logic(car_pos_t *car, frog_pos_t *frog, uint32_t frame, uint32_t *buffer)
{
    if (car->x == frog->x && car->y == frog->y && car->resetTimer == 0)
    {
        triggerLoss(&GameState, frame);
        return;
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
}

bool handleLossVictory(uint32_t frame, uint32_t *buffer)
{
    if (!GameState.hasWon && FrogPos.x >= FULL_ROW_LEN - 1)
    {
        triggerWin(&GameState, frame);
    }

    bool ret = false;
    if (GameState.hasLost)
    {
        display_splat(buffer, &FrogPos, frame - GameState.gameEndFrame);
        ret = true;
    }
    else if (GameState.hasWon)
    {
        display_victory(buffer, frame - GameState.gameEndFrame);
        //set_hat_full_color(buffer, WIN_COLOR);
        ret = true;
    }

    if (checkForReset(&GameState, frame))
    {
        frogger_init();
    }

    return ret;
}

// This is the "render" call currently called every 20ms in main (20ms > 6ms so should be fine) (nextFrameTime = currTime + 20 * 1000;)
void frogger_produce_output(uint32_t frame, uint32_t *buffer)
{
    srand(42);
    blank_buffer(buffer);

    if (!handleLossVictory(frame, buffer))
    {
        for (int i = 0; i < NUM_CARS; i++)
        {
            car_logic(&car_positions[i], &FrogPos, frame, buffer);
        }

        // This API lets you "write" on a 21x10 grid - and for higher rows interpolates to find the nearest actual LED
        // So our current frog controls are argubally bad (on higher rows left / right won't actually cause movement)
        write_pixel(buffer, FrogPos.x, FrogPos.y, GameState.hasLost ? DEAD_COLOR : FROG_COLOR);

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
        if (FrogPos.x < FULL_ROW_LEN - 1)
        {
            FrogPos.x++;
        }

        break;
    }
    }
}
