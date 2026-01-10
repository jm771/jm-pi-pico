#include "dma_helpers.h"

void dma_init(uint channel, uint dreq, volatile void *write_addr, dma_channel_transfer_size_t size)
{
    dma_channel_claim(channel);
    dma_channel_config_t config = dma_channel_get_default_config(channel);
    dma_channel_config_t *conf = &config;
    channel_config_set_read_address_update_type(conf, DMA_ADDRESS_UPDATE_INCREMENT);
    channel_config_set_write_address_update_type(conf, DMA_ADDRESS_UPDATE_NONE);
    // Probably needs to match bits per transfer?
    channel_config_set_transfer_data_size(conf, size);
    channel_config_set_enable(conf, true);
    channel_config_set_dreq(conf, dreq);
    dma_channel_set_config(channel, conf, false);
    dma_channel_set_write_addr(channel, write_addr, false);

    // spi_get_hw(spi)->dmacr |= 0x2;
}

void dma_send_buffer(uint dma_channel, void const *buffer, size_t len)
{
    dma_channel_set_read_addr(dma_channel, buffer, false);
    dma_channel_set_trans_count(dma_channel, dma_encode_transfer_count(len), true);
}