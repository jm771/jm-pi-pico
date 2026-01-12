/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// #include <string.h>

// #include "pico/cyw43_arch.h"
// #include "pico/stdlib.h"

// #include "lwip/pbuf.h"
// #include "lwip/tcp.h"

// #include "dhcpserver.h"
// #include "dnsserver.h"

#include "picow_access_point.h"

int server_init()
{
    stdio_init_all();

    static TCP_SERVER_T server; // state = calloc(1, sizeof(TCP_SERVER_T));
    TCP_SERVER_T *state = &server;

    if (cyw43_arch_init())
    {
        DEBUG_printf("failed to initialise\n");
        return 1;
    }

    const char *ap_name = "picow_test";
    const char *password = "password";

    cyw43_arch_enable_ap_mode(ap_name, password, CYW43_AUTH_WPA2_AES_PSK);

    ip4_addr_t mask;
    state->gw.addr = PP_HTONL(CYW43_DEFAULT_IP_AP_ADDRESS);
    mask.addr = PP_HTONL(CYW43_DEFAULT_IP_MASK);

    // Start the dhcp server
    static dhcp_server_t dhcp_server;
    dhcp_server_init(&dhcp_server, &state->gw, &mask);

    // Start the dns server
    static dns_server_t dns_server;
    dns_server_init(&dns_server, &state->gw);

    if (!tcp_server_open(state, ap_name))
    {
        DEBUG_printf("failed to open server\n");
        return 1;
    }

    return 0;
}

int main()
{
    if (server_init())
    {
        return 1;
    }

    while (true)
    {
        cyw43_arch_poll();
        // Could use this to sleep untime time or until cyw43_arch_poll() has work to do:
        // cyw43_arch_wait_for_work_until(make_timeout_time_ms(1000));
    }

    return 0;
}

// This would shut down server / access point
// tcp_server_close(state);
// dns_server_deinit(&dns_server);
// dhcp_server_deinit(&dhcp_server);
// cyw43_arch_deinit();
// printf("Test complete\n");