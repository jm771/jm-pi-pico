#include "joystick.h" 
#include <stdio.h>
#include "pico/stdlib.h"

void init_joystick(){
	for(int i = JOYSTICK_PIN_BASE; i < JOYSTICK_PIN_BASE + JOYSTICK_PIN_COUNT; i++){
		gpio_init(i);
		gpio_set_dir(i, GPIO_IN);
		gpio_pull_up(i);
	}
};

enum dir_e get_joystick_pos(){
	if ( gpio_get(JOYSTOCK_PIN_UP) == false ) return UP;
	if ( gpio_get(JOYSTOCK_PIN_DOWN) == false ) return DOWN;
	if ( gpio_get(JOYSTOCK_PIN_LEFT) == false ) return LEFT;
	if ( gpio_get(JOYSTOCK_PIN_RIGHT) == false ) return RIGHT;
	return NONE;
};

