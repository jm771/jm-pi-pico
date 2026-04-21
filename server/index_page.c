#include "index_page.h"
#include <stdint.h>
#include "main_led_driver.h"
#include "band_controler.h"
#include "accesspoint_defines.h"
#include <assert.h>
#include "server_utils.h"
#include "frogger_page.h"

#define INDEX_BODY_START "<html><body><h1>Hello from Hat</h1><p>Selected program is %s</p>"
#define INDEX_BODY_END "</body><link rel=\"stylesheet\" href=\"styles.css\"></html>"
#define BUTTON_STRING "<p><a href=\"?led=%u\">%s</a></p>"
#define BAND_STRING "<p><a href=\"?%s=%u\">%s</a></p>"
#ifdef WIFI_SUPPORTED
static_assert(sizeof(INDEX_BODY_START) + sizeof(INDEX_BODY_END) < MAX_RESPONSE_LENGTH);
#endif
#define LED_PARAM "led=%lu"
#define RED_BAND_PARAM "red=%lu"
#define LED_GPIO 0
#define FORM_BEGIN "<form action=\"/submit\" method=\"get\">"
#define FORM_BAND_BRIGHTNESS "<label>Band Brightness:<input type=\"range\" name=\"gain\" min=\"0\" max=\"16\" value=\"%u\"></label><output></output>"
#define FROM_BAND_ON "<label>Band on<input type=\"checkbox\" checked=\"true\">"
#define FORM_END "<br><br><button>Submit</button></form>"

static uint32_t *selectedProgram;
static band_settings_t *bandSettings;

void index_page_init(uint32_t *selectedProgramRef, band_settings_t *bandSettingsRef)
{
    selectedProgram = selectedProgramRef;
    bandSettings = bandSettingsRef;
}

void serve_index_content(const char *params, TCP_RESPONSE_T *result)
{
    // See if the user changed it
    if (params)
    {
        // TODO - could assert only one match
        if (sscanf(params, LED_PARAM, selectedProgram) != EOF)
        {
            if (*selectedProgram == FROGGER_PROGRAM)
            {
                write_redirect_header(result, FROGGER_ENDPOINT);
                return;
            }
        }

        uint32_t redParam;
        if (sscanf(params, RED_BAND_PARAM, &redParam) == 1)
        {
            bandSettings->red = redParam;
        }
        printf("red %hhu\n", bandSettings->red);
    }

    append_to_response(result, INDEX_BODY_START, GetProgramNames()[*selectedProgram]);

    for (size_t i = 0; i < N_PROGS; i++)
    {
        append_to_response(result, BUTTON_STRING, i, GetProgramNames()[i]);
    }

    // append_to_response(result, BAND_STRING, "red", !(bandSettings->red), bandSettings->red ? "red off" : "red on");

    append_to_response(result, INDEX_BODY_END);

    append_to_response(result, FORM_BEGIN);
    append_to_response(result, FORM_BAND_BRIGHTNESS, bandSettings->brightness);
    append_to_response(result, FROM_BAND_ON);
    append_to_response(result, FORM_END);

    (void)bandSettings;
}