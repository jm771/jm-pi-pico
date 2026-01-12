#include "dotstar_utils.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "dma_helpers.h"

#define N_DOTS 64
#define N_FRAMES (N_DOTS + 2)
#define FRAME_SIZE 4
#define BUFFER_SIZE (N_FRAMES * FRAME_SIZE)

static uint8_t Buffer[BUFFER_SIZE];
static uint8_t Channel;

void init_buffer()
{
    // START_FRAME
    Buffer[0] = 0x00;
    Buffer[1] = 0x00;
    Buffer[2] = 0x00;
    Buffer[3] = 0x00;

    // END_FRAME
    Buffer[(N_DOTS + 1) * FRAME_SIZE + 0] = 0xff;
    Buffer[(N_DOTS + 1) * FRAME_SIZE + 1] = 0xff;
    Buffer[(N_DOTS + 1) * FRAME_SIZE + 2] = 0xff;
    Buffer[(N_DOTS + 1) * FRAME_SIZE + 3] = 0xff;
}

void write_pixel_to_buffer(uint32_t rgb, uint8_t brightness, uint8_t *buffer_out)
{
    buffer_out[0] = 0xE0;          // Must lead with 111
    buffer_out[0] |= (brightness); // 5 bits of brightness infp
    buffer_out[1] = rgb >> 0;      // B
    buffer_out[2] = rgb >> 8;      // G
    buffer_out[3] = rgb >> 16;     // R
}

void dotstar_init()
{
    init_buffer();

    spi_inst_t *spi = spi0;
    // Set SPI format
    // Initialize SPI port at 1 MHz
    // LEDs are speced to work between 800 and 1200 Khz
    spi_init(spi, 1000 * 1000);

    spi_set_format(spi,        // SPI instance
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

    Channel = dma_init(DREQ_SPI0_TX, &spi_get_hw(spi)->dr, DMA_SIZE_8);
}

void dotstar_write_pattern(uint32_t const *input, size_t len)
{
    (void)len;

    // 0 to 31
    uint8_t const BRIGHTNESS = 1;

    uint8_t *const data_start = Buffer + FRAME_SIZE;

    for (size_t i = 0; i < N_DOTS; i++)
    {
        write_pixel_to_buffer(input[i], BRIGHTNESS, data_start + FRAME_SIZE * i);
    }

    // spi_write_blocking(spi0, Buffer, BUFFER_SIZE);

    dma_send_buffer(Channel, Buffer, BUFFER_SIZE);
}