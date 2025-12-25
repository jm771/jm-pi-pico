#include "text_utils.h"
#include "hat_utils.h"
#include "stddef.h"
#include <stdio.h>

uint32_t get_4pt_width(char character)
{
    switch (character)
    {
    case 'a':
    case 'd':
    case 'l':
        return 3;
    case 'm':
        return 5;
    case 'u':
        return 3;
    default:
        return 4;
    }
}

char *get_4pt_char(char character)
{
    switch (character)
    {
    case 'a':
        return " # \n"
               "# #\n"
               "###\n"
               "# #\n";
    case 'd':
        return "## \n"
               "# #\n"
               "# #\n"
               "## \n";
    case 'l':
        return "#  \n"
               "#  \n"
               "#  \n"
               "###\n";
    case 'm':
        return " # # \n"
               "# # #\n"
               "# # #\n"
               "# # #\n";

    case 'u':
        return "# #\n"
               "# #\n"
               "# #\n"
               "###\n";
    default:
        return "####\n"
               "####\n"
               "####\n"
               "####\n";
    }
}

uint32_t get_8pt_width(char character)
{
    switch (character)
    {
    case 'e':
        return 6;
    case 'm':
        return 8;
    case 'r':
        return 7;
    default:
        return 4;
    }
}

char *get_8pt_char(char character)
{
    switch (character)
    {
    case 'e':
        return "######\n"
               "##   #\n"
               "##\n"
               "####\n"
               "####\n"
               "##\n"
               "##   #\n"
               "######\n";
    case 'm':
        return "########\n"
               "########\n"
               "## ## ##\n"
               "## ## ##\n"
               "## ## ##\n"
               "## ## ##\n"
               "## ## ##\n"
               "## ## ##\n";
    case 'r':
        return "#####\n"
               "######\n"
               "##  ##\n"
               "##  ##\n"
               "#####\n"
               "## ##\n"
               "##  ##\n"
               "##   ##\n";
    default:
        return "####\n"
               "####\n"
               "####\n"
               "####\n";
    }
}

void write_character(uint32_t *buffer, char *string, uint32_t color, uint32_t x, uint32_t y, uint32_t min_x, uint32_t max_x)
{
    printf("writing\n");
    uint32_t j = y;
    // uint32_t i = x;
    uint32_t x_off = 0;

    for (; *string != '\0'; string++)
    {
        if (*string == '\n')
        {
            j--;
            x_off = 0;
            // printf("\n");
        }
        else
        {
            if (*string == '#')
            {
                if (x_off >= min_x && x_off < max_x)
                {
                    write_pixel(buffer, ((x + x_off) % FULL_ROW_LEN), j, color);
                }
                // printf("#");
            }
            // else
            // {
            //     write_pixel(buffer, ((x + x_off) % FULL_ROW_LEN), j, 0);
            //     // printf(" ");
            // }
            x_off++;
        }
    }
}

uint32_t write_char_4pt(uint32_t *buffer, char character, uint32_t color, uint32_t x, uint32_t y)
{
    uint32_t const width = get_4pt_width(character);
    write_character(buffer, get_4pt_char(character), color, x, y, 0, width);
    return width;
}

uint32_t write_char_8pt(uint32_t *buffer, char character, uint32_t color, uint32_t x_off, tr)
{
    write_character(buffer, get_8pt_char(character), color, x_off, 7);
    return get_8pt_width(character);
}