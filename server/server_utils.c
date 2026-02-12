#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include "picow_access_point.h"

#define HTTP_RESPONSE_HEADERS "HTTP/1.1 %d OK\nContent-Length: %d\nContent-Type: text/html; charset=utf-8\nConnection: close\n\n"
#define HTTP_RESPONSE_REDIRECT "HTTP/1.1 302 Redirect\nLocation: http://%s/%s\n\n"

__attribute__((format(printf, 3, 4))) static inline void
format_to_buffer(char **outArray_p, size_t *max_result_len_p, char const *format, ...)
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

__attribute__((format(printf, 2, 3))) void append_to_response(TCP_RESPONSE_T *response, char const *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    int max_result_length = MAX_RESPONSE_LENGTH - response->result_len;
    int result = vsnprintf(response->result + response->result_len, max_result_length, format, argptr);
    va_end(argptr);

    if (result > max_result_length)
    {
        result = max_result_length;
    }

    response->result_len += result;
}

void reset_content(TCP_RESPONSE_T *response)
{
    response->result_len = 0;
}

void write_success_header(TCP_RESPONSE_T *con_state)
{
    con_state->header_len = snprintf(con_state->headers, sizeof(con_state->headers), HTTP_RESPONSE_HEADERS,
                                     200, con_state->result_len);
}

void write_redirect_header(TCP_RESPONSE_T *con_state, char const *relpath)
{
    ip4_addr_t gw;
    gw.addr = PP_HTONL(CYW43_DEFAULT_IP_AP_ADDRESS);
    con_state->header_len = snprintf(con_state->headers, sizeof(con_state->headers), HTTP_RESPONSE_REDIRECT,
                                     ipaddr_ntoa(&gw), relpath);
    DEBUG_printf("Sending redirect %s", con_state->headers);
}