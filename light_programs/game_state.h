#include "pico/types.h"

#define N_LEVELS 2

typedef struct
{
    bool hasLost;
    bool hasWon;
    uint32_t level;
    uint32_t gameEndFrame;
} game_state_t;

void game_state_init(game_state_t *gameState);

void triggerLoss(game_state_t *gameState, uint32_t frame);

void triggerWin(game_state_t *gameState, uint32_t frame);

bool checkForReset(game_state_t *gameState, uint32_t frame);