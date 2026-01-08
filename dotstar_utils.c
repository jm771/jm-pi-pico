#include "dotstar_utils.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

typedef union
{
    uint32_t value;
    uint8_t bytes[4];
} converter_t;

void add_frame_header(converter_t *data, uint8_t brightness)
{
    data->bytes[0] = 0xE0;
    data->bytes[0] |= (brightness >> 3);
}

void dotstar_init()
{
    spi_inst_t *spi = spi0;
    // Set SPI format
    // Initialize SPI port at 1 MHz
    // LEDs are speced to work between 800 and 1200 Khz
    spi_init(spi, 1000 * 1000);

    spi_set_format(spi0, // SPI instance
                   8,    // Number of bits per transfer (Valid values 4..16.)
                   1,    // Polarity (CPOL)
                   1,    // Phase (CPHA)
                   SPI_MSB_FIRST);

    // These are the pins physically connected to the spi0 interface
    const uint sck_pin = 18;
    const uint mosi_pin = 19;

    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    // gpio_set_function(miso_pin, GPIO_FUNC_SPI);
}

void dotstar_write_pattern(uint32_t const *buffer, size_t len)
{
    spi_inst_t *spi = spi0;

    converter_t const startFrame = {0};
    converter_t const endFrame = {0xffffffff};

    converter_t pixel;

    spi_write_blocking(spi, startFrame.bytes, 4);

    for (size_t i = 0; i < len; i++)
    {
        pixel.value = buffer[i];
        add_frame_header(&pixel, 0xff);
        spi_write_blocking(spi, pixel.bytes, 4);
    }

    spi_write_blocking(spi, endFrame.bytes, 4);

    // const uint cs_pin = 17;

    // const uint miso_pin = 16;
}