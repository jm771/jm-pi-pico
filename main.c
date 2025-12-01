#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "hardware/pio.h"
#include "ws2812.pio.h" 
#include "ws2812_utils.h" 

#define WS2812_FREQ 800000 
#define OTHER_LED_PIN 0 

#define INC 1
#define DELAY 50 

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
	int l = 0;
    int u = 0;
	bool led = true; 

    while (true)
    {
		


        gpio_put(PICO_DEFAULT_LED_PIN,led );
        sleep_ms(DELAY);
        enum dir_e joystick_pos = get_joystick_pos();

		
        if (joystick_pos & UP) {
			printf("hello");
			u = u == 20 ? u : u+INC;
		}
        if (joystick_pos & DOWN) {
			u = u == 0 ? 0 : u-INC;
		}
        if (joystick_pos & LEFT) {
			l = l == 255 ? 255 : l+INC;
		}
        if (joystick_pos & RIGHT) {
			l = l == 0 ? 0 : l-INC;
		}


        printf("Joystick new %i %d %d\n", joystick_pos, u, l);
        for (int i = 0; i < 20; i++)
		{
			if ( i < u ) put_pixel(pio, sm, rand());
			else put_pixel(pio, sm, urgb_u32(255, l, 255-l));
		}
		//	else { put_pixel(pio, sm, 0); }

		//	if (i & joystick_pos) {
		//	put_pixel(pio,sm, rand());
		//	puput_pixel(pio, sm, urgb_u32(255, u, 255-u));
		//	puput_pixel(pio, sm, urgb_u32(255, l, 255-l));
		//	pu//	}
		//}
		led = !led; 
    }

    return 0;
}
