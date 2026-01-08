#include "dotstar_utils.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

typedef struct
{
    uint8_t bytes[4];
} frame_t;

static frame_t const START_FRAME = {0};
static frame_t const END_FRAME = {{0xff, 0xff, 0xff, 0xff}};

frame_t from_rgb_brightness(uint32_t rgb, uint8_t brightness)
{
    frame_t pixel;
    pixel.bytes[0] = 0xE0;          // Must lead with 111
    pixel.bytes[0] |= (brightness); // 5 bits of brightness infp
    pixel.bytes[1] = rgb >> 0;      // B
    pixel.bytes[2] = rgb >> 8;      // G
    pixel.bytes[3] = rgb >> 16;     // R
    return pixel;
}

void write_frame_blocking(frame_t pixel)
{
    spi_inst_t *spi = spi0;
    spi_write_blocking(spi, pixel.bytes, 4);
}

void dotstar_init()
{
    spi_inst_t *spi = spi0;
    // Set SPI format
    // Initialize SPI port at 1 MHz
    // LEDs are speced to work between 800 and 1200 Khz
    spi_init(spi, 1000 * 1000);

    spi_set_format(spi0,       // SPI instance
                   8,          // Number of bits per transfer (Valid values 4..16.)
                   SPI_CPOL_1, // Polarity (CPOL)
                   SPI_CPHA_1, // Phase (CPHA)
                   SPI_LSB_FIRST);

    // These are the pins physically connected to the spi0 interface
    const uint sck_pin = 18;
    const uint mosi_pin = 19;

    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    // gpio_set_function(miso_pin, GPIO_FUNC_SPI);
}

void dotstar_write_pattern(uint32_t const *buffer, size_t len)
{

    // 0 to 31
    uint8_t const brightness = 2;

    write_frame_blocking(START_FRAME);

    for (size_t i = 0; i < len; i++)
    {
        // pixel.value = buffer[i];
        write_frame_blocking(from_rgb_brightness(buffer[i], brightness));
    }

    write_frame_blocking(END_FRAME);
}