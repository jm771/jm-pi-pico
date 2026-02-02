#include "game_state.h"

void game_state_init(game_state_t *gameState)
{
    gameState->hasLost = false;
    gameState->hasWon = false;
}

void triggerLoss(game_state_t *gameState, uint32_t frame)
{
    gameState->hasLost = true;
    gameState->gameEndFrame = frame;
}

void triggerWin(game_state_t *gameState, uint32_t frame)
{
    gameState->hasWon = true;
    gameState->gameEndFrame = frame;
}

bool checkForReset(game_state_t *gameState, uint32_t frame)
{
    if (gameState->hasLost || gameState->hasWon)
    {
        if (frame > gameState->gameEndFrame + 50 * 3)
        {
            game_state_init(gameState);
            return true;
        }
    }
    return false;
}