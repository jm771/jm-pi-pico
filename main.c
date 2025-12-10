#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "ws2812_utils.h"
#include "joystick_prog.h"

#define WS2812_FREQ 800000
#define OTHER_LED_PIN 0

#define DELAY 50
#define N_LEDS 200
#define BRIGHNESS_SHIFT 3

int main()
{
    uint32_t buffer[N_LEDS];

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
    bool led = true;

    while (true)
    {

        gpio_put(PICO_DEFAULT_LED_PIN, led);
        sleep_ms(DELAY);

        joystick_prog_produce_output(0, buffer, N_LEDS);

        for (int i = 0; i < N_LEDS; i++)
        {
            put_pixel(pio, sm, adjustBrightness(buffer[i], BRIGHNESS_SHIFT));
        }

        led = !led;
    }

    return 0;
}
