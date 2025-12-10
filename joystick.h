#ifndef JOYSTICK_H
#define JOYSTICK_H

#define JOYSTICK_PIN_COUNT 4
#define JOYSTICK_PIN_BASE 2

#define JOYSTOCK_PIN_UP 5    // 2
#define JOYSTOCK_PIN_DOWN 4  // 3
#define JOYSTOCK_PIN_LEFT 3  // 4
#define JOYSTOCK_PIN_RIGHT 2 // 5

enum dir_e
{
    NONE = 0,
    UP = 1 << 0,
    DOWN = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3
};

void init_joystick();

enum dir_e get_joystick_pos();

#endif