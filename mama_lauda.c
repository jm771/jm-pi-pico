#include "mama_lauda.h"
#include "text_utils.h"
#include "hat_utils.h"

#define MARGIN 1
#define PRETEND_WIDTH (ROW_WIDTH - 3)

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

uint32_t pixel_len(char const *string)
{
    uint32_t ret = 0;
    for (char const *c = string; *c != '\0'; c++)
    {
        ret += MARGIN + get_8pt_width(*c);
    }

    return ret;
}

void write_string(unsigned int frame, char const *string, uint32_t *buffer)
{
    uint32_t const total_len = pixel_len(string) + PRETEND_WIDTH;
    int32_t const scroll_offset = (frame % total_len) - PRETEND_WIDTH;

    uint32_t pixel_in_string = 0;
    uint32_t char_in_str = 0;

    for (char const *c = string; *c != '\0'; c++)
    {
        uint32_t const char_width = get_8pt_width(*c);

        if ((int32_t)pixel_in_string >= scroll_offset + PRETEND_WIDTH)
        {
            break;
        }

        if ((int32_t)(pixel_in_string + char_width) >= scroll_offset)
        {
            write_char_8pt(buffer, *c, 0xff << 8 * (char_in_str % 3), pixel_in_string - scroll_offset);
        }

        pixel_in_string += MARGIN + get_8pt_width(*c);
        char_in_str++;
    }
}

void mama_lauda_produce_output(unsigned int frame, uint32_t *buffer)
{
    // (void)frame;
    blank_buffer(buffer);

    write_string(frame / 10, "merry", buffer);
}

// uint32_t offset = FULL_ROW_LEN - (frame / 20) % FULL_ROW_LEN;
// uint32_t offset = 0;

// uint32_t x = offset;

// (void)x;
// write_pixel(buffer, 0, 0, 0xff0000);
// write_pixel(buffer, 6, 0, 0x00ff00);
// write_pixel(buffer, 13, 0, 0x0000ff);
// write_pixel(buffer, 20, 0, 0xfffff);
// x += write_char_8pt(buffer, 'm', 0xff, x, 7) + MARGIN;
// x += write_char_8pt(buffer, 'e', 0xff00, x, 7) + MARGIN;
// x += write_char_8pt(buffer, 'r', 0xff, x, 8) + MARGIN;
// x += write_char_4pt(buffer, 'r', 0xff00, x, 8) + MARGIN;
// x += write_char_4pt(buffer, 'y', 0xff00, x, 8) + MARGIN;

// x = offset;

// x += write_char_4pt(buffer, 'l', 0xff00ff, x, 3) + MARGIN; // purple
// x += write_char_4pt(buffer, 'a', 0xffff00, x, 3) + MARGIN; // cyan
// x += write_char_4pt(buffer, 'u', 0x00ffff, x, 3) + MARGIN; // yellow
// x += write_char_4pt(buffer, 'd', 0xff0000, x, 3) + MARGIN; // blue
// x += write_char_4pt(buffer, 'a', 0xff00ff, x, 3) + MARGIN;
// }