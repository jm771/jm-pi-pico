#ifdef WIFI_SUPPORTED
#include "pico/cyw43_arch.h"
#include "picow_access_point.h"
#endif

#include "main_led_driver.h"

#define INDEX_BODY_START "<html><body><h1>Hello from Hat</h1><p>Selected program is %s</p>"
#define INDEX_BODY_END "</body><link rel=\"stylesheet\" href=\"styles.css\"><</html>"
#define BUTTON_STRING "<p><a href=\"?led=%lu\">%s</a></p>"
static_assert(sizeof(INDEX_BODY_START) + sizeof(INDEX_BODY_END) < MAX_RESPONSE_LENGTH);
#define LED_PARAM "led=%lu"
#define INDEX_ENDPOINT "/index.html"
#define STYLES_ENDPOINT "/styles.css"
#define LED_GPIO 0

static int test_server_content(const char *request, const char *params, char *result, size_t max_result_len);

static uint32_t *selectedProgram;

int server_init(uint32_t *selectedProgramRef)
{
#ifdef WIFI_SUPPORTED
    selectedProgram = selectedProgramRef;
    cyw43_arch_init();

    static TCP_SERVER_T server; // state = calloc(1, sizeof(TCP_SERVER_T));
    server.http_response_handler = test_server_content;
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

static int
serve_test_server_content(const char *params, char *result, size_t max_result_len)
{
    // See if the user changed it
    if (params)
    {
        // TODO - could assert only one match
        sscanf(params, LED_PARAM, selectedProgram);
    }

    char const *startResult = result;

    format_to_buffer(&result, &max_result_len, INDEX_BODY_START, GetProgramNames()[*selectedProgram]);

    for (size_t i = 0; i < N_PROGS; i++)
    {
        format_to_buffer(&result, &max_result_len, BUTTON_STRING, i, GetProgramNames()[i]);
    }

    format_to_buffer(&result, &max_result_len, INDEX_BODY_END);

    return result - startResult;
}

#define BG_PRIMARY "#1e1e1e"
#define TEXT_PRIMARY
#define ACCENT_BLUE "#4fc3f7"
static const char THE_CSS[] = "body{font-family:Segoe UI;background-color:" BG_PRIMARY ";color:#d4d4d4;font-size:16px}"
                              "a{background-color:" ACCENT_BLUE ";border:none;border-radius:8px;color:" BG_PRIMARY ";"
                              "padding: 12px 24px;}";
//;
// font-size : 16px;
// font - weight : 600;
// cursor : pointer;
// transition : all.2s ease;
// "

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