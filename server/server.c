#ifdef WIFI_SUPPORTED
#include "pico/cyw43_arch.h"
#include "picow_access_point.h"
#endif

#define LED_TEST_BODY "<html><body><h1>Hello from Pico.</h1><p>Led is %s</p><p><a href=\"?led=%d\">Turn led %s</a></body></html>"
#define LED_PARAM "led=%d"
#define INDEX_ENDPOINT "/index.html"
#define LED_GPIO 0

static int test_server_content(const char *request, const char *params, char *result, size_t max_result_len);

int server_init()
{
#ifdef WIFI_SUPPORTED
    cyw43_arch_init();

    static TCP_SERVER_T server; // state = calloc(1, sizeof(TCP_SERVER_T));
    server.http_response_handler = test_server_content;
    TCP_SERVER_T *state = &server;

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
#endif
    return 0;
}

static int test_server_content(const char *request, const char *params, char *result, size_t max_result_len)
{
    int len = 0;
    if (strncmp(request, INDEX_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        // Get the state of the led
        bool value;
        cyw43_gpio_get(&cyw43_state, LED_GPIO, &value);
        int led_state = value;

        // See if the user changed it
        if (params)
        {
            int led_param = sscanf(params, LED_PARAM, &led_state);
            if (led_param == 1)
            {
                if (led_state)
                {
                    // Turn led on
                    cyw43_gpio_set(&cyw43_state, LED_GPIO, true);
                }
                else
                {
                    // Turn led off
                    cyw43_gpio_set(&cyw43_state, LED_GPIO, false);
                }
            }
        }
        // Generate result
        if (led_state)
        {
            len = snprintf(result, max_result_len, LED_TEST_BODY, "ON", 0, "OFF");
        }
        else
        {
            len = snprintf(result, max_result_len, LED_TEST_BODY, "OFF", 1, "ON");
        }
    }
    return len;
}

void server_poll()
{
#ifdef WIFI_SUPPORTED
    cyw43_arch_poll();
#endif
}