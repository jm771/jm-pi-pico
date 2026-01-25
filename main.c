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
#include "band_controler.h"
#include "pico/cyw43_arch.h"
#include "pwm.h"
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

static uint32_t selectedProgram = STARTING_PROGRAM;
static band_settings_t bandSettings;

void main_init()
{
    pwm_install_program();
    dotstar_init();
    stdio_init_all();
    band_controller_init(&bandSettings);
    server_init(&selectedProgram, &bandSettings);
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
            // dotstar_test();
            main_led_poll(frame, selectedProgram);
            set_onboard_led(led);
            bandSettings.red = (bandSettings.red + 1) % 256;
            band_controller_poll(&bandSettings);

            led = !led;
            frame++;

            nextFrameTime = currTime + 20 * 1000;

            // printf("Processed in %llu\n", get_absolute_time() - currTime);
        }
        else
        {
            cyw43_arch_wait_for_work_until(make_timeout_time_ms(1));
        }
    }

    return 0;
}
