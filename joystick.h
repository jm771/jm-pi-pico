#define JOYSTICK_PIN_COUNT 4 
#define JOYSTICK_PIN_BASE 2 

#define JOYSTOCK_PIN_UP    2
#define JOYSTOCK_PIN_DOWN  3
#define JOYSTOCK_PIN_LEFT  4
#define JOYSTOCK_PIN_RIGHT 5

enum dir_e {NONE, UP, DOWN, LEFT, RIGHT};

void init_joystick(); 

enum dir_e get_joystick_pos();

