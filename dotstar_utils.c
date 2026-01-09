#include "dotstar_utils.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

typedef struct
{
    uint8_t bytes[4];
} frame_t;

// static frame_t const START_FRAME = {0};
// static frame_t const END_FRAME = {{0xff, 0xff, 0xff, 0xff}};

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

// INTE1 to disable interupts

void dma_init(spi_inst_t *spi)
{
    dma_channel_claim(0);
    dma_channel_config_t config = dma_channel_get_default_config(0);
    dma_channel_config_t *conf = &config;
    channel_config_set_read_address_update_type(conf, DMA_ADDRESS_UPDATE_INCREMENT);
    channel_config_set_write_address_update_type(conf, DMA_ADDRESS_UPDATE_NONE);
    // TODO could swap
    channel_config_set_transfer_data_size(conf, DMA_SIZE_8);
    channel_config_set_enable(conf, true);
    channel_config_set_dreq(conf, DREQ_SPI0_TX);
    dma_channel_set_config(0, conf, false);
    dma_channel_set_write_addr(0, &spi_get_hw(spi)->dr, false);

    spi_get_hw(spi)->dmacr |= 0x2;

    // dmacr
}

void dotstar_init()
{
    // 4.4.3.16. PrimeCell DMA interface
    // DMA_CH0_READ_ADDR

    spi_inst_t *spi = spi0;
    // Set SPI format
    // Initialize SPI port at 1 MHzv
    // LEDs are speced to work between 800 and 1200 Khz
    spi_init(spi, 1000 * 1000);

    spi_set_format(spi0,       // SPI instance
                   8,          // Number of bits per transfer (Valid values 4..16.)
                   SPI_CPOL_1, // Polarity (CPOL)
                   SPI_CPHA_1, // Phase (CPHA)
                   SPI_LSB_FIRST);

    const uint sck_pin = 18;
    const uint mosi_pin = 19;

    // Mux these pins which SPI function a pin does is a property of the physical pin
    // Easy physical pin is only connected to MOSI MISO or CLK on one off SPI1 or SPI2
    // See PI PICO datasheet "function select"
    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    // gpio_set_function(miso_pin, GPIO_FUNC_SPI);

    dma_init(spi);
}

void dotstar_write_pattern(uint32_t const *input, size_t len)
{
    (void)len;

    // assert(len == 64);
    static uint8_t buffer[4 * (64 + 2)];

    buffer[0] = 0x00;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x00;

    buffer[65 * 4 + 0] = 0xff;
    buffer[65 * 4 + 1] = 0xff;
    buffer[65 * 4 + 2] = 0xff;
    buffer[65 * 4 + 3] = 0xff;

    // 0 to 31
    uint8_t const brightness = 1;

    // write_frame_blocking(START_FRAME);

    uint8_t *data_start = buffer + 4;

    for (size_t i = 0; i < 64; i++)
    {
        // pixel.value = buffer[i];
        frame_t point = from_rgb_brightness(input[i], brightness);
        // spi_write_blocking(spi0, point.bytes, 4);
        for (size_t j = 0; j < 4; j++)
        {
            // spi_write_blocking(spi0, point.bytes + j, 1);
            data_start[4 * i + j] = point.bytes[j];
        }
    }

    // spi_write_blocking(spi0, buffer, 66 * 4);

    dma_channel_set_read_addr(0, &buffer, false);
    dma_channel_set_trans_count(0, dma_encode_transfer_count(4 * (64 + 2)), true);

    // spi_inst_t *spi = spi0;
    // spi_write_blocking(spi, buffer, 4 * (64 + 2));

    // for (size_t i = 0; i < 4 * (64 + 2); i++)
    // {
    //     spi_write_blocking(buffer, , pixel.bytes, 4);
    // }

    // write_frame_blocking(END_FRAME);
}