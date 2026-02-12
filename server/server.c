#ifdef WIFI_SUPPORTED
#include "pico/cyw43_arch.h"
#include "picow_access_point.h"
#endif

#include <stddef.h>
#include "frogger_page.h"
#include "frogger.h"
#include "css.h"
#include "index_page.h"
#include <band_controler.h>

#ifdef WIFI_SUPPORTED
#define BODY_SEPARATOR "\r\n\r\n"

static void handle_post_request(const char *request, TCP_RESPONSE_T *result)
{
    char const *sep_point = strstr(request, BODY_SEPARATOR);
    if (sep_point)
    {
        char const *body = sep_point + sizeof(BODY_SEPARATOR) - 1;
        printf("handling this body\n%s\n\n", body);
        frogger_accept_keypress(*body);
    }

    write_success_header(result);
}

static void handle_server_request(const char *request, const char *params, TCP_RESPONSE_T *result)
{
    if (strncmp(request, INDEX_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        return serve_index_content(params, result);
    }
    else if (strncmp(request, "/" FROGGER_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        return serve_frogger_content(params, result);
    }
    else if (strncmp(request, STYLES_ENDPOINT, sizeof(STYLES_ENDPOINT) - 1) == 0)
    {
        return serve_css(params, result);
    }
    else
    {
        write_redirect_header(result, "index.html");
        return;
    }

    write_success_header(result);
}
#endif

int server_init(uint32_t *selectedProgramRef, band_settings_t *bandSettingsRef)
{
#ifdef WIFI_SUPPORTED
    index_page_init(selectedProgramRef, bandSettingsRef);

    cyw43_arch_init();

    static TCP_SERVER_T server; // state = calloc(1, sizeof(TCP_SERVER_T));
    server.get_response_handler = handle_server_request;
    server.post_response_handler = handle_post_request;
    TCP_SERVER_T *state = &server;

    const char *ap_name = "wifi-hatspot";
    const char *password = "hatsarefun";

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
#endif
    return 0;
}

void server_poll()
{
#ifdef WIFI_SUPPORTED
    cyw43_arch_poll();
#endif
}