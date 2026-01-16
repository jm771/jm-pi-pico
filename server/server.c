#ifdef WIFI_SUPPORTED
#include "pico/cyw43_arch.h"
#include "picow_access_point.h"
#endif

#define INDEX_BODY "<html><body><h1>Hello from Pico.</h1><p>Led is %s</p><p><button href=\"?led=%d\">Turn led %s</button></body><link rel=\"stylesheet\" href=\"styles.css\"></html>"
static_assert(sizeof(INDEX_BODY) < MAX_RESPONSE_LENGTH);
#define LED_PARAM "led=%d"
#define INDEX_ENDPOINT "/index.html"
#define STYLES_ENDPOINT "/styles.css"
#define LED_GPIO 0

static int test_server_content(const char *request, const char *params, char *result, size_t max_result_len);

int server_init()
{
#ifdef WIFI_SUPPORTED
    cyw43_arch_init();

    static TCP_SERVER_T server; // state = calloc(1, sizeof(TCP_SERVER_T));
    server.http_response_handler = test_server_content;
    TCP_SERVER_T *state = &server;

    const char *ap_name = "hatpoint";
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

static int serve_test_server_content(const char *params, char *result, size_t max_result_len)
{
    // Get the state of the led
    bool value;
    cyw43_gpio_get(&cyw43_state, LED_GPIO, &value);
    int led_state = value;
    int len = 0;

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
        len = snprintf(result, max_result_len, INDEX_BODY, "ON", 0, "OFF");
    }
    else
    {
        len = snprintf(result, max_result_len, INDEX_BODY, "OFF", 1, "ON");
    }

    return len;
}

#define BG_PRIMARY "#1e1e1e"
#define THE_CSS "body{font-family:Segoe UI;background-color:#1e1e1e;color:#d4d4d4}" \
                "a{background-color:#4fc3f7;border:none;border-radius:8px;color:" BG_PRIMARY "";
padding : 12px 24px;
font - size : 16px;
font - weight : 600;
cursor : pointer;
transition : all.2s ease;
"

    static_assert(sizeof(THE_CSS) < MAX_RESPONSE_LENGTH);

static int serve_css(const char *params, char *result, size_t max_result_len)
{
    (void)params;
    return snprintf(result, max_result_len, THE_CSS);
}

static int test_server_content(const char *request, const char *params, char *result, size_t max_result_len)
{

    if (strncmp(request, INDEX_ENDPOINT, sizeof(INDEX_ENDPOINT) - 1) == 0)
    {
        return serve_test_server_content(params, result, max_result_len);
    }

    if (strncmp(request, STYLES_ENDPOINT, sizeof(STYLES_ENDPOINT) - 1) == 0)
    {
        return serve_css(params, result, max_result_len);
    }

    return 0;
}

void server_poll()
{
#ifdef WIFI_SUPPORTED
    cyw43_arch_poll();
#endif
}