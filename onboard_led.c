#include "onboard_led.h"
#include "pico/stdlib.h"

void onboard_led_init()
{
    gpio_init(19);
    gpio_set_dir(19, GPIO_OUT);
    gpio_init(20);
    gpio_set_dir(20, GPIO_OUT);
    gpio_init(21);
    gpio_set_dir(21, GPIO_OUT);

    // only defined on pico 1
    // #ifdef PICO_DEFAULT_LED_PIN
    //     gpio_init(PICO_DEFAULT_LED_PIN);
    //     gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    // #endif
}

void set_onboard_led(bool on)
{
    //     static uint32_t count;
    //     count++;

    //     if (count % 4 != 0)
    //     {
    //         return;
    //     }

    //     // if (count % 3 == 0)
    //     // {
    //     //     printf("0\n");
    //     //     // gpio_put(21, 1); // Green - inverted - acting weird
    //     //     // gpio_put(20, 0); // Red - working
    //     //     // gpio_put(19, 1); // This one is blue and not working
    //     // }
    //     // if (count % 3 == 1)
    //     // {
    //     //     printf("1\n");
    //     //     // gpio_put(21, 0);
    //     //     // gpio_put(20, 1); // Red - working
    //     //     // gpio_put(19, 1); // This one is blue and not working
    //     // }
    //     // if (count % 3 == 2)
    //     // {
    //     //     printf("2\n");
    //     //     // gpio_put(21, 0);
    //     //     // gpio_put(20, 0); // Red - working
    //     //     // gpio_put(19, 0); // This one is blue and not working
    //     // }

    (void)on;
    //     // Turning off for now as the demo also uses the LED
    //     // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);

    //     // #ifdef PICO_DEFAULT_LED_PIN
    //     //     gpio_put(PICO_DEFAULT_LED_PIN, on);
    //     // #elifdef CYW43_WL_GPIO_LED_PIN
    //     //     // gpio_put(WL_GPIO0, on);
    //     // #else
    //     // #error Need to define some sort on on board LED
    //     // #endif
}