#include "css.h"
#include "accesspoint_defines.h"
#include "stdio.h"
#include "server_utils.h"
#include <assert.h>

#define BG_PRIMARY "#1e1e1e"
#define TEXT_PRIMARY
#define ACCENT_BLUE "#4fc3f7"
static const char THE_CSS[] = "body{font-family:Segoe UI;background-color:" BG_PRIMARY ";color:#d4d4d4;font-size:24px}"
                              "a{background-color:" ACCENT_BLUE ";border:none;border-radius:8px;color:" BG_PRIMARY ";"
                              "padding: 12px 24px;}";
//;
// font-size : 16px;
// font - weight : 600;
// cursor : pointer;
// transition : all.2s ease;
// "

static_assert(sizeof(THE_CSS) < MAX_RESPONSE_LENGTH);

void serve_css(const char *params, TCP_RESPONSE_T *result)
{
    (void)params;
    append_to_response(result, THE_CSS);
}