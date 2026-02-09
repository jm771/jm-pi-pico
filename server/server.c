#ifdef WIFI_SUPPORTED
#include "pico/cyw43_arch.h"
#include "picow_access_point.h"
#endif

#include <stddef.h>
#include "frogger_page.h"
#include "css.h"
#include "index_page.h"

#ifdef WIFI_SUPPORTED
static int handle_server_request(const char *request, const char *params, char *result, size_t max_result_len);
#endif

int server_init(uint32_t *selectedProgramRef, band_settings_t *bandSettingsRef)
{
    selectedProgram = selectedProgramRef;
    bandSettings = bandSettingsRef;
#ifdef WIFI_SUPPORTED

    cyw43_arch_init();

    static TCP_SERVER_T server; // state = calloc(1, sizeof(TCP_SERVER_T));
    server.http_response_handler = handle_server_request;
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

#ifdef WIFI_SUPPORTED
void format_to_buffer(char **outArray_p, size_t *max_result_len_p, char const *format, ...)
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

static int handle_server_request(const char *request, const char *params, char *result, size_t max_result_len)
{

    if (strncmp(request, INDEX_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        return serve_test_server_content(params, result, max_result_len);
    }
    if (strncmp(request, FROGGER_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        return serve_frogger_content(params, result, max_result_len);
    }

    if (strncmp(request, STYLES_ENDPOINT, sizeof(STYLES_ENDPOINT) - 1) == 0)
    {
        return serve_css(params, result, max_result_len);
    }

    return 0;
}

#endif

void server_poll()
{
#ifdef WIFI_SUPPORTED
    cyw43_arch_poll();
#endif
}