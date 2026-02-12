#include "frogger.h"
#include "frogger_page.h"
#include "stdio.h"
#include "server_utils.h"

#define CSS                                     \
    "body {"                                    \
    "background: #1b1b1b;"                      \
    "color: #fff;"                              \
    "font-family: \"Courier New\", monospace;"  \
    "display: flex;"                            \
    "flex-direction: column;"                   \
    "align-items: center;"                      \
    "justify-content: center;"                  \
    "height: 100vh;"                            \
    "margin: 0;"                                \
    "}"                                         \
    "table {"                                   \
    "border-collapse: separate;"                \
    "border-spacing: 10px;"                     \
    "}"                                         \
    "button {"                                  \
    "width: 72px;"                              \
    "height: 72px;"                             \
    "background: #2a2a2a;"                      \
    "color: #f2f2f2;"                           \
    "border: 4px solid #000;"                   \
    "border-radius: 4px;"                       \
    "font-size: 14px;"                          \
    "cursor: pointer;"                          \
    "}"                                         \
    "button:active {"                           \
    "transform: scale(0.96);"                   \
    "}"                                         \
    "#up, #down, #left, #right {"               \
    "background: #3a3a3a;"                      \
    "}"                                         \
    "button {"                                  \
    "touch-action: none;"                       \
    "-webkit-tap-highlight-color: transparent;" \
    "user-select: none;"                        \
    "}"

#define FROGGER_CONTENT                                                                                                      \
    "<html>"                                                                                                                 \
    "<head>"                                                                                                                 \
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">"        \
    "</head>"                                                                                                                \
    "<body>Frogger!<table>"                                                                                                  \
    "<tr><td/><td>"                                                                                                          \
    "<button id=\"up\">&#x25B2;</button>"                                                                                    \
    "</td><td/></tr>"                                                                                                        \
    "<tr><td>"                                                                                                               \
    "<button id=\"left\">&#x25C0;</button>"                                                                                  \
    "</td><td/><td>"                                                                                                         \
    "<button id=\"right\">&#x25B6;</button>"                                                                                 \
    "</td></tr>"                                                                                                             \
    "<tr><td/><td>"                                                                                                          \
    "<button id=\"down\">&#x25BC;</button>"                                                                                  \
    "</td><td/></tr>"                                                                                                        \
    "</table></body><script>"                                                                                                \
    "document.getElementById(\"left\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 'a', })};"  \
    "document.getElementById(\"right\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 'd', })};" \
    "document.getElementById(\"up\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 'w', })};"    \
    "document.getElementById(\"down\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 's', })};"  \
    "</script>"                                                                                                              \
    "<style>" CSS                                                                                                            \
    "</style>"                                                                                                               \
    "</html>"

void serve_frogger_content(char const *params, TCP_RESPONSE_T *result)
{

    (void)params;
    // frogger_accept_keypress('d');
    append_to_response(result, FROGGER_CONTENT);
}