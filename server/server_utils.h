#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAX_RESPONSE_LENGTH 4096
#define HTTP_GET "GET"

typedef struct
{
    char headers[1024];
    char result[MAX_RESPONSE_LENGTH];
    int header_len;
    int result_len;
} TCP_RESPONSE_T;

typedef void (*http_get_response_handler_t)(const char *, const char *, TCP_RESPONSE_T *);
typedef void (*http_post_response_handler_t)(const char *, TCP_RESPONSE_T *);

void reset_content(TCP_RESPONSE_T *response);

__attribute__((format(printf, 2, 3))) void append_to_response(TCP_RESPONSE_T *response, char const *format, ...);

void write_success_header(TCP_RESPONSE_T *con_state);
void write_redirect_header(TCP_RESPONSE_T *con_state, char const *relpath);
void handle_http_request(char * http_request, TCP_RESPONSE_T * result, http_get_response_handler_t get_response_handler,
    http_post_response_handler_t post_response_handler);

#ifdef WIFI_SUPPORTED
void handle_post_request(const char *request, TCP_RESPONSE_T *result);

void handle_server_request(const char *request, const char *params, TCP_RESPONSE_T *result);

#endif

#endif