#include "index_page.h"
#include <stdint.h>
#include "main_led_driver.h"
#include "band_controler.h"
#include "accesspoint_defines.h"
#include <assert.h>
#include "server_utils.h"

#define INDEX_BODY_START "<html><body><h1>Hello from Hat</h1><p>Selected program is %s</p><a href=\"/frogger.html\">Frogger Link</a>"
#define INDEX_BODY_END "</body><link rel=\"stylesheet\" href=\"styles.css\"></html>"
#define BUTTON_STRING "<p><a href=\"?%s=%lu\">%s</a></p>"
#define BAND_STRING "<p><a href=\"?%s=%lu\">%s</a></p>"
#ifdef WIFI_SUPPORTED
static_assert(sizeof(INDEX_BODY_START) + sizeof(INDEX_BODY_END) < MAX_RESPONSE_LENGTH);
#endif
#define LED_PARAM "led=%lu"
#define RED_BAND_PARAM "red=%lu"
#define LED_GPIO 0
#define FORM_BEGIN "<form action=\"/submit\" method=\"get\">"
#define FORM_RED "<label>Red:<input type=\"range\" name=\"gain\" min=\"0\" max=\"10\" value=\"5\"></label><output></output>"
#define FORM_END "<br><br><button>Submit</button></form>"

static uint32_t *selectedProgram;
static band_settings_t *bandSettings;

void index_page_init(uint32_t *selectedProgramRef, band_settings_t *bandSettingsRef)
{
    selectedProgram = selectedProgramRef;
    bandSettings = bandSettingsRef;
}

int serve_test_server_content(const char *params, char *result, size_t max_result_len)
{
    // See if the user changed it
    if (params)
    {
        // TODO - could assert only one match
        sscanf(params, LED_PARAM, selectedProgram);
        // printf("selects %lu", *selectedProgram);
        uint32_t redParam;
        if (sscanf(params, RED_BAND_PARAM, &redParam) == 1)
        {
            bandSettings->red = redParam;
        }
        printf("red %hhu\n", bandSettings->red);
    }

    char const *startResult = result;

    format_to_buffer(&result, &max_result_len, INDEX_BODY_START, GetProgramNames()[*selectedProgram]);

    for (size_t i = 0; i < N_PROGS; i++)
    {
        format_to_buffer(&result, &max_result_len, BUTTON_STRING, i, GetProgramNames()[i]);
    }

    format_to_buffer(&result, &max_result_len, BAND_STRING, "red", !(bandSettings->red), bandSettings->red ? "red off" : "red on");

    format_to_buffer(&result, &max_result_len, INDEX_BODY_END);

    format_to_buffer(&result, &max_result_len, FORM_BEGIN);
    format_to_buffer(&result, &max_result_len, FORM_RED);
    format_to_buffer(&result, &max_result_len, FORM_END);

    (void)bandSettings;

    return result - startResult;
}