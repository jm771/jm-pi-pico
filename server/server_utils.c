#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#include "server_utils.h"
#include "index_page.h"
#include "frogger_page.h"
#include "css.h"

#ifndef DEBUG_SERVER
#include "frogger.h"
#endif

#define HTTP_RESPONSE_HEADERS "HTTP/1.1 %d OK\r\nContent-Length: %d\r\nContent-Type: text/html; charset=utf-8\r\nConnection: close\r\n\r\n"
#define HTTP_RESPONSE_REDIRECT "HTTP/1.1 302 Redirect\r\nLocation: http://%s/%s\r\nContent-Length: 0\r\nConnection: close\r\n\r\n"

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
    response->header_len = 0;
}

void write_success_header(TCP_RESPONSE_T *con_state)
{
    con_state->header_len = snprintf(con_state->headers, sizeof(con_state->headers), HTTP_RESPONSE_HEADERS,
                                     200, con_state->result_len);
}

void write_redirect_header(TCP_RESPONSE_T *con_state,  char const *relpath)
{
    // ip4_addr_t gw;
    // gw.addr = PP_HTONL(CYW43_DEFAULT_IP_AP_ADDRESS);
    // ipaddr_ntoa(&gw)

    #ifdef DEBUG_SERVER
    static const char * IP_ADDR = "localhost:1337";
    #else
    static const char * IP_ADDR = "192.168.4.1";
    #endif

    con_state->header_len = snprintf(con_state->headers, sizeof(con_state->headers), HTTP_RESPONSE_REDIRECT,
                                    IP_ADDR, relpath);
    printf("Sending redirect %s", con_state->headers);
}

void handle_http_request(char * http_request, TCP_RESPONSE_T * result, http_get_response_handler_t get_response_handler,
    http_post_response_handler_t post_response_handler)
{  
        reset_content(result);

        // Handle GET request
        if (strncmp(HTTP_GET, http_request, sizeof(HTTP_GET) - 1) == 0)
        {
            char *request = http_request + sizeof(HTTP_GET); // + space
            char *eol = strchr(request, '\n');
            char *params = memchr(request, '?', eol-request);

            if (params)
            {
                if (*params)
                {
                    char *space = strchr(request, ' ');
                    *params++ = 0;
                    if (space)
                    {
                        *space = 0;
                    }
                }
                else
                {
                    params = NULL;
                }
            }

            // Generate content
            get_response_handler(request, params, result);
        }
        else if (strncmp("POST", http_request, sizeof("POST") - 1) == 0)
        {
            post_response_handler(http_request, result);
        }
        else
        {
            //TODO
            write_redirect_header(result, "index.html");
        }

}

#define BODY_SEPARATOR "\r\n\r\n"

void handle_post_request(const char *request, TCP_RESPONSE_T *result)
{
    char const *sep_point = strstr(request, BODY_SEPARATOR);
    if (sep_point)
    {
        char const *body = sep_point + sizeof(BODY_SEPARATOR) - 1;
        printf("handling this body\n%s\n\n", body);

        if (strstr(request, "POST /frogger.html"))
        {
            #ifndef DEBUG_SERVER
            frogger_accept_keypress(*body);
            #endif
        }
        else if (strstr(request, "POST /band"))
        {
            bool on = (strcmp(body, "true") == 0);
            set_band_enabled(on);
            printf("setting %i\n", on);
        }
    }

    write_success_header(result);
}

void handle_server_request(const char *request, const char *params, TCP_RESPONSE_T *result)
{
    if (strncmp(request, INDEX_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        serve_index_content(params, result);
    }
    else if (strncmp(request, "/" FROGGER_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        serve_frogger_content(params, result);
    }
    else if (strncmp(request, STYLES_ENDPOINT, sizeof(STYLES_ENDPOINT) - 1) == 0)
    {
        serve_css(params, result);
    }
    else
    {
        write_redirect_header(result, "index.html");
        return;
    }

    if (result->header_len == 0)
    {
        write_success_header(result);
    }
}