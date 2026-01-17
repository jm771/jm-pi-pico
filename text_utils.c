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

uint32_t get_6pt_width(char character)
{
    switch (character)
    {
    case 'a':
        return 3;
    case 'd':
        return 3;
    case 'e':
        return 4;
    case 'l':
        return 4;
    case 'm':
        return 5;
    case 'r':
        return 4;
    case 'u':
        return 3;
    case 'y':
        return 3;
    case ' ':
        return 3;
    default:
        return 4;
    }
}

char *get_6pt_char(char character)
{
    switch (character)
    {
    case 'a':
        return "###\n"
               "# #\n"
               "# #\n"
               "###\n"
               "# #\n"
               "# #\n";
    case 'd':
        return "##\n"
               "# #\n"
               "# #\n"
               "# #\n"
               "# #\n"
               "##\n";

    case 'e':
        return "####\n"
               "#\n"
               "####\n"
               "#\n"
               "#\n"
               "####\n";
    case 'l':
        return "#\n"
               "#\n"
               "#\n"
               "#\n"
               "#\n"
               "####\n";
    case 'm':
        return "#####\n"
               "#####\n"
               "# # #\n"
               "# # #\n"
               "# # #\n"
               "# # #\n";
    case 'r':
        return "###\n"
               "# #\n"
               "###\n"
               "# #\n"
               "# ##\n"
               "#  #\n";
    case 'u':
        return "# #\n"
               "# #\n"
               "# #\n"
               "# #\n"
               "# #\n"
               "###\n";
    case 'y':
        return "# #\n"
               "# #\n"
               "###\n"
               " #\n"
               " #\n"
               " #\n";
    case ' ':
        return "";
    default:
        return "####\n"
               "####\n"
               "####\n"
               "####\n";
    }
}

void write_character(uint32_t *buffer, char *string, uint32_t color, int32_t x, int32_t y)
{
    // printf("writing\n");
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
                const int32_t x_res = x_off + x;
                // TODO this is a nasty back
                if (x_res >= 0 && x_res < ROW_WIDTH - 3)
                {
                    write_pixel(buffer, x_res, j, color);
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

uint32_t write_char_4pt(uint32_t *buffer, char character, uint32_t color, int32_t x, int32_t y)
{
    uint32_t const width = get_4pt_width(character);
    write_character(buffer, get_4pt_char(character), color, x, y);
    return width;
}

void write_char_6pt(uint32_t *buffer, char character, uint32_t color, int32_t x_off)
{
    write_character(buffer, get_6pt_char(character), color, x_off, 5);
    // return get_8pt_width(character);
}