#include "ws2812_utils.h" 

void set_chain(PIO pio, uint8_t sm, uint32_t *color, size_t l){
	hard_assert(color);
	hard_assert(l);

	for(size_t i=0; i < l; i++){
		put_pixel(pio, sm, color[i]);
	}
}
