#include "mama_lauda.h"
#include "text_utils.h"
#include "hat_utils.h"

#define MARGIN 0

void mama_lauda_produce_output(unsigned int frame, uint32_t *buffer)
{
    (void)frame;
    blank_buffer(buffer);

    // uint32_t offset = FULL_ROW_LEN - (frame / 20) % FULL_ROW_LEN;
    uint32_t offset = 0;

    uint32_t x = offset;
    x += write_char_4pt(buffer, 'm', 0xff, x, 8) + MARGIN;
    x += write_char_4pt(buffer, 'a', 0xff00, x, 8) + MARGIN;
    x += write_char_4pt(buffer, 'm', 0xff, x, 8) + MARGIN;
    x += write_char_4pt(buffer, 'a', 0xff00, x, 8) + MARGIN;

    x = offset;

    x += write_char_4pt(buffer, 'l', 0xff00ff, x, 3) + MARGIN; // purple
    x += write_char_4pt(buffer, 'a', 0xffff00, x, 3) + MARGIN; // cyan
    x += write_char_4pt(buffer, 'u', 0x00ffff, x, 3) + MARGIN; // yellow
    x += write_char_4pt(buffer, 'd', 0xff0000, x, 3) + MARGIN; // blue
    x += write_char_4pt(buffer, 'a', 0xff00ff, x, 3) + MARGIN;
}