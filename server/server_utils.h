#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

static inline void format_to_buffer(char **outArray_p, size_t *max_result_len_p, char const *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    int result = vsnprintf(*outArray_p, *max_result_len_p, format, argptr);
    va_end(argptr);

    if (result > (int)*max_result_len_p)
    {
        result = (int)*max_result_len_p;
    }

    *max_result_len_p -= result;
    *outArray_p += result;
}

#endif