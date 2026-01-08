#include "dotstar_utils.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

void init()
{
    spi_inst_t *spi = spi0;
    // Set SPI format
    // Initialize SPI port at 1 MHz
    spi_init(spi, 1000 * 1000);

    spi_set_format(spi0, // SPI instance
                   8,    // Number of bits per transfer
                   1,    // Polarity (CPOL)
                   1,    // Phase (CPHA)
                   SPI_MSB_FIRST);

    // Initialize SPI pins
    const uint sck_pin = 18;
    const uint mosi_pin = 19;

    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    // gpio_set_function(miso_pin, GPIO_FUNC_SPI);
}

void write_pattern(uint32_t const *buffer)
{
    (void)buffer;
    spi_inst_t *spi = spi0;

    uint8_t msg[] = {0, 1};

    spi_write_blocking(spi, msg, 2);
    // const uint cs_pin = 17;

    // const uint miso_pin = 16;
}