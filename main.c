#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "hardware/pio.h"
#include "ws2812.pio.h" 
#include "ws2812_utils.h" 

#define WS2812_FREQ 800000 
#define OTHER_LED_PIN 0 

int main()
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    init_joystick();
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    stdio_init_all();



    // PIO 
    PIO pio;
    uint sm;
    uint offset;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, OTHER_LED_PIN, 1, true);
    hard_assert(success);
    ws2812_program_init(pio, sm, offset, OTHER_LED_PIN, WS2812_FREQ);

    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(200);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(200);
        printf("Joystick %i\n", get_joystick_pos());
		put_pixel(pio,sm, rand());
    }

    return 0;
}
