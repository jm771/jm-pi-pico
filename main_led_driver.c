#include "main_led_driver.h"
#include "joystick_prog.h"
#include "spinning_rainbow.h"
#include "mama_lauda.h"
#include "stars.h"
#include "pixels.h"

#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "ws2812_utils.h"
#include "dma_helpers.h"

#define WS2812_FREQ 800000
#define MAIN_LED_PIN 0
#define N_LEDS 200
#define BRIGHNESS_SHIFT 3

static uint8_t MainLedChannel;
static uint32_t MainLedBuffer[N_LEDS];
static const char *ProgramNames[] = {"Spinning Rainbow", "Stars", "Blocks", "Text"};

const char **GetProgramNames()
{
    return ProgramNames;
}

void main_led_init()
{
    PIO pio;
    uint sm;
    uint offset;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, MAIN_LED_PIN, 1, true);
    hard_assert(success);
    ws2812_program_init(pio, sm, offset, MAIN_LED_PIN, WS2812_FREQ);

    MainLedChannel = dma_init(pio_get_dreq(pio, sm, true), &(pio->txf[sm]), DMA_SIZE_32);
    main_led_blank();
}

void main_led_blank()
{
    blank_buffer(MainLedBuffer);
    dma_send_buffer(MainLedChannel, MainLedBuffer, N_LEDS * sizeof(uint32_t));
}

void run_selected_program(uint32_t frame, uint32_t program_number, uint32_t *buffer)
{
    switch (program_number)
    {
    case 0:
        return spinning_rainbow_produce_output(frame, buffer);
    case 1:
        return stars_produce_output(frame, buffer);
    case 2:
        return pixels_produce_output(frame, buffer);
    case 3:
        return mama_lauda_produce_output(frame, buffer);
    }
}

void main_led_poll(uint32_t frame, uint32_t program_number)
{
    static uint32_t LedDrawBuffer[N_LEDS];

    run_selected_program(frame, program_number, MainLedBuffer);

    for (int i = 0; i < N_LEDS; i++)
    {
        LedDrawBuffer[i] = adjustBrightness(MainLedBuffer[i], BRIGHNESS_SHIFT) << 8u;
    }

    dma_send_buffer(MainLedChannel, LedDrawBuffer, N_LEDS);
}