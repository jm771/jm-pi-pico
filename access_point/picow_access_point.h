#ifndef PICOW_ACCESS_POINT_H
#define PICOW_ACCESS_POINT_H

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#include "dhcpserver.h"
#include "dnsserver.h"

#define DEBUG_printf printf
#define MAX_RESPONSE_LENGTH 4096

typedef struct TCP_SERVER_T_
{
    struct tcp_pcb *server_pcb;
    ip_addr_t gw;
    // todo - tyepdef:
    int (*http_response_handler)(const char *, const char *, char *, size_t);
} TCP_SERVER_T;

typedef struct TCP_CONNECT_STATE_T_
{
    struct tcp_pcb *pcb;
    int sent_len;
    char headers[128];
    char result[MAX_RESPONSE_LENGTH];
    int header_len;
    int result_len;
    ip_addr_t *gw;
    TCP_SERVER_T *parent;
} TCP_CONNECT_STATE_T;

bool tcp_server_open(TCP_SERVER_T *state, const char *ap_name);
void tcp_server_close(TCP_SERVER_T *state);

#endif