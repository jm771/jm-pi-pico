#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#define MAX_RESPONSE_LENGTH 4096

typedef struct
{
    char headers[1024];
    char result[MAX_RESPONSE_LENGTH];
    int header_len;
    int result_len;
} TCP_RESPONSE_T;

void reset_content(TCP_RESPONSE_T *response);

__attribute__((format(printf, 2, 3))) void append_to_response(TCP_RESPONSE_T *response, char const *format, ...);

void write_success_header(TCP_RESPONSE_T *con_state);
void write_redirect_header(TCP_RESPONSE_T *con_state, char const *relpath);

#endif