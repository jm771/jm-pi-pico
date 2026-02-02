#include "joystick.h"
#include <stdio.h>
#include "pico/stdlib.h"

static dir_t LastState = NONE;

void init_joystick()
{
	for (int i = JOYSTICK_PIN_BASE; i < JOYSTICK_PIN_BASE + JOYSTICK_PIN_COUNT; i++)
	{
		gpio_init(i);
		gpio_set_dir(i, GPIO_IN);
		gpio_pull_up(i);
	}
}

dir_t get_joystick_pos()
{
	dir_t ret = NONE;
	ret |= (gpio_get(JOYSTOCK_PIN_UP) == false) ? UP : 0;
	ret |= (gpio_get(JOYSTOCK_PIN_DOWN) == false) ? DOWN : 0;
	ret |= (gpio_get(JOYSTOCK_PIN_LEFT) == false) ? LEFT : 0;
	ret |= (gpio_get(JOYSTOCK_PIN_RIGHT) == false) ? RIGHT : 0;
	return ret;
}

// Only supports new inputs - not releases
void joystick_poll(dir_event_handler_t dir_event_handler)
{
	dir_t currentDir = get_joystick_pos();
	dir_t new_directions = currentDir & ~LastState;

	if (new_directions)
	{
		dir_event_handler(new_directions);
	}

	LastState = currentDir;
}