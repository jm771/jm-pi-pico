#ifndef JOYSTICK_H
#define JOYSTICK_H

#define JOYSTICK_PIN_COUNT 4
#define JOYSTICK_PIN_BASE 2

#define JOYSTOCK_PIN_UP 5    // 2
#define JOYSTOCK_PIN_DOWN 4  // 3
#define JOYSTOCK_PIN_LEFT 3  // 4
#define JOYSTOCK_PIN_RIGHT 2 // 5

typedef enum
{
    NONE = 0,
    UP = 1 << 0,
    DOWN = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3
} dir_t;

typedef void (*dir_event_handler_t)(dir_t);

#define N_JOYSTICK_DIRS 4
#define JOYSTICK_DIR_MASK ((1 << N_JOYSTICK_DIRS) - 1)

void init_joystick();

dir_t get_joystick_pos();

dir_t get_joystick_events();

void joystick_poll(dir_event_handler_t dir_event_handler);

#endif