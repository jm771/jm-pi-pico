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

// int main()
// {
//     if (server_init())
//     {
//         return 1;
//     }

//     while (true)
//     {
//         cyw43_arch_poll();
//         // Could use this to sleep untime time or until cyw43_arch_poll() has work to do:
//         // cyw43_arch_wait_for_work_until(make_timeout_time_ms(1000));
//     }

//     return 0;
// }

// This would shut down server / access point
// tcp_server_close(state);
// dns_server_deinit(&dns_server);
// dhcp_server_deinit(&dhcp_server);
// cyw43_arch_deinit();
// printf("Test complete\n");