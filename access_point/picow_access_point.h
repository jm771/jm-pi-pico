#ifndef PICOW_ACCESS_POINT_H
#define PICOW_ACCESS_POINT_H

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#include "dhcpserver.h"
#include "dnsserver.h"
#include "accesspoint_defines.h"

#define DEBUG_printf printf

typedef int (*http_get_response_handler_t)(const char *, const char *, char *, size_t);
typedef int (*http_post_response_handler_t)(const char *, char *, size_t);

typedef struct TCP_SERVER_T_
{
    struct tcp_pcb *server_pcb;
    ip_addr_t gw;
    // todo - tyepdef:
    http_get_response_handler_t get_response_handler;
    http_post_response_handler_t post_response_handler;
} TCP_SERVER_T;

typedef struct TCP_CONNECT_STATE_T_
{
    struct tcp_pcb *pcb;
    int sent_len;
    char headers[2048];
    char result[MAX_RESPONSE_LENGTH];
    int header_len;
    int result_len;
    ip_addr_t *gw;
    TCP_SERVER_T *parent;
} TCP_CONNECT_STATE_T;

bool tcp_server_open(TCP_SERVER_T *state, const char *ap_name);
void tcp_server_close(TCP_SERVER_T *state);

#endif