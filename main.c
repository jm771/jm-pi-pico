#include <stdio.h>
#include "pico/stdlib.h"
#include "joystick.h"

int main()
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    init_joystick();
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    stdio_init_all();

    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(200);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(200);
        printf("Joystick %i\n", get_joystick_pos());
    }

    return 0;
}
