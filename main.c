#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "pico/bootrom.h"
#include "tusb.h"
#include "dotstar_utils.h"
#include "dma_helpers.h"
#include "onboard_led.h"
#include "main_led_driver.h"
#include "server.h"
// #include "pico/status_led.h"

bool letsReset = false;

// magic interupt name for recieving a character over com (over USB)
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

void main_init()
{
    dotstar_init();
    stdio_init_all();
    server_init();
    onboard_led_init();

    init_joystick();

    tusb_init();
    main_led_init();
}

int main()
{

    main_init();

    bool led = true;

    int64_t nextFrameTime = 0;
    int32_t frame = 0;
    uint32_t incer = 0;

    int debouncing = 0;

    while (true)
    {
        tud_task();
        server_poll();
        if (letsReset)
        {
            main_led_blank();
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

            dotstar_test();
            main_led_poll(frame, incer % N_PROGS);
            set_onboard_led(led);

            led = !led;

            nextFrameTime = currTime + 20 * 1000;

            printf("Processed in %llu\n", get_absolute_time() - currTime);
        }
    }

    return 0;
}
