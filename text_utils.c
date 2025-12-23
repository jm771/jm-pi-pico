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

uint32_t write_char_4pt(uint32_t *buffer, char character, uint32_t color, uint32_t x, uint32_t y)
{
    printf("writing\n");
    char *string = get_4pt_char(character);
    uint32_t j = y;
    uint32_t i = x;

    for (; *string != '\0'; string++)
    {
        if (*string == '\n')
        {
            j--;
            i = x;
            printf("\n");
        }
        else
        {
            if (*string == '#')
            {
                write_pixel(buffer, (i % FULL_ROW_LEN), j, color);
                printf("#");
            }
            else
            {
                write_pixel(buffer, (i % FULL_ROW_LEN), j, 0);
                printf(" ");
            }
            i++;
        }
    }

    return get_4pt_width(character);
}