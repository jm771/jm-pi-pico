#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "ws2812_utils.h"
#include "joystick_prog.h"
#include "spinning_rainbow.h"
#include "mama_lauda.h"
#include "stars.h"
#include "pixels.h"
#include "pico/bootrom.h"
#include "tusb.h"
#include "dotstar_utils.h"

#define WS2812_FREQ 800000
#define OTHER_LED_PIN 0

#define DELAY 50
#define N_LEDS 200
#define BRIGHNESS_SHIFT 3
#define N_PROGS 4

bool letsReset = false;

void tud_cdc_rx_cb(uint8_t itf)
{
    (void)itf;
    while (tud_cdc_available())
    {
        char c = tud_cdc_read_char();
        if (c == 'r')
        {
            letsReset = true;
        }
    }
}

int main()
{
    uint32_t buffer[N_LEDS];

    dotstar_init();
    gpio_init(PICO_DEFAULT_LED_PIN);
    init_joystick();
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    stdio_init_all();
    tusb_init();

    // PIO
    PIO pio;
    uint sm;
    uint offset;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, OTHER_LED_PIN, 1, true);
    hard_assert(success);
    ws2812_program_init(pio, sm, offset, OTHER_LED_PIN, WS2812_FREQ);
    bool led = true;

    int64_t nextFrameTime = 0;
    int32_t frame = 0;
    uint32_t incer = 0;

    int debouncing = 0;

    while (true)
    {
        tud_task();
        if (letsReset)
        {
            blank_buffer(buffer);
            for (int i = 0; i < N_LEDS; i++)
            {
                put_pixel(pio, sm, 0);
            }
            reset_usb_boot(0, 0);
        }

        int64_t currTime = get_absolute_time();

        if (currTime > nextFrameTime)
        {
            enum dir_e joystick_pos = get_joystick_pos();

            if (joystick_pos & UP)
            {
                if (!debouncing)
                    incer++;
                debouncing = 1;
            }
            else if (joystick_pos & DOWN)
            {
                if (!debouncing)
                    incer--;
                debouncing = 1;
            }
            else
            {
                debouncing = 0;
            }

            gpio_put(PICO_DEFAULT_LED_PIN, led);

            // joystick_prog_produce_output(frame, buffer, N_LEDS);
            if (incer % N_PROGS == 0)
            {
                spinning_rainbow_produce_output(frame, buffer);
            }
            if (incer % N_PROGS == 1)
            {
                stars_produce_output(frame, buffer);
            }
            if (incer % N_PROGS == 2)
            {
                pixels_produce_output(frame, buffer);
            }
            if (incer % N_PROGS == 3)
            {
                mama_lauda_produce_output(frame, buffer);
            }

            // uint32_t color = 0xff0000;

            // This wants BGR colours

            uint32_t pixels[64];

            memset(pixels, 0, 64 * sizeof(uint32_t));

            for (size_t i = 0; i < 64; i += 4)
            {
                pixels[i] = 0xff0000;     // R
                pixels[i + 1] = 0xff00;   // G
                pixels[i + 2] = 0xff;     // B
                pixels[i + 3] = 0xffffff; // B
            }

            dotstar_write_pattern(pixels, 64);

            frame++;

            // TODO - would be cooler to DMA this
            for (int i = 0; i < N_LEDS; i++)
            {
                put_pixel(pio, sm, adjustBrightness(buffer[i], BRIGHNESS_SHIFT));
            }

            led = !led;

            nextFrameTime = currTime + 20 * 1000;

            printf("Processed in %llu\n", get_absolute_time() - currTime);
        }
    }

    return 0;
}
