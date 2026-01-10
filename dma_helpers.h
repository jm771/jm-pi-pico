#ifndef DMA_HELPERS_H
#define DMA_HELPERS_H

#include "pico/types.h"
#include "hardware/dma.h"

void dma_init(uint channel, uint dreq, volatile void *write_addr, dma_channel_transfer_size_t size);

void dma_send_buffer(uint channel, void const *buffer, size_t len);

#endif