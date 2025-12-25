#include "mama_lauda.h"
#include "text_utils.h"
#include "hat_utils.h"

// #define MARGIN 0
#define MARGIN 2

// void mama_lauda_produce_output(unsigned int frame, uint32_t *buffer)
// {
//     (void)frame;
//     blank_buffer(buffer);

//     // uint32_t offset = FULL_ROW_LEN - (frame / 20) % FULL_ROW_LEN;
//     uint32_t offset = 0;

//     uint32_t x = offset;
//     x += write_char_4pt(buffer, 'm', 0xff, x, 8) + MARGIN;
//     x += write_char_4pt(buffer, 'a', 0xff00, x, 8) + MARGIN;
//     x += write_char_4pt(buffer, 'm', 0xff, x, 8) + MARGIN;
//     x += write_char_4pt(buffer, 'a', 0xff00, x, 8) + MARGIN;

//     x = offset;

//     x += write_char_4pt(buffer, 'l', 0xff00ff, x, 3) + MARGIN; // purple
//     x += write_char_4pt(buffer, 'a', 0xffff00, x, 3) + MARGIN; // cyan
//     x += write_char_4pt(buffer, 'u', 0x00ffff, x, 3) + MARGIN; // yellow
//     x += write_char_4pt(buffer, 'd', 0xff0000, x, 3) + MARGIN; // blue
//     x += write_char_4pt(buffer, 'a', 0xff00ff, x, 3) + MARGIN;
// }

void mama_lauda_produce_output(unsigned int frame, uint32_t *buffer)
{
    (void)frame;
    blank_buffer(buffer);

    // uint32_t offset = FULL_ROW_LEN - (frame / 20) % FULL_ROW_LEN;
    uint32_t offset = 0;

    uint32_t x = offset;
    // (void)x;
    // write_pixel(buffer, 0, 0, 0xff0000);
    // write_pixel(buffer, 6, 0, 0x00ff00);
    // write_pixel(buffer, 13, 0, 0x0000ff);
    // write_pixel(buffer, 20, 0, 0xfffff);
    x += write_char_8pt(buffer, 'm', 0xff, x, 7) + MARGIN;
    x += write_char_8pt(buffer, 'e', 0xff00, x, 7) + MARGIN;
    x += write_char_8pt(buffer, 'r', 0xff, x, 8) + MARGIN;
    // x += write_char_4pt(buffer, 'r', 0xff00, x, 8) + MARGIN;
    // x += write_char_4pt(buffer, 'y', 0xff00, x, 8) + MARGIN;

    // x = offset;

    // x += write_char_4pt(buffer, 'l', 0xff00ff, x, 3) + MARGIN; // purple
    // x += write_char_4pt(buffer, 'a', 0xffff00, x, 3) + MARGIN; // cyan
    // x += write_char_4pt(buffer, 'u', 0x00ffff, x, 3) + MARGIN; // yellow
    // x += write_char_4pt(buffer, 'd', 0xff0000, x, 3) + MARGIN; // blue
    // x += write_char_4pt(buffer, 'a', 0xff00ff, x, 3) + MARGIN;
}