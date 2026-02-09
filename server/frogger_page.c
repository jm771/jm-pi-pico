#include "frogger.h"
#include "frogger_page.h"
#include "stdio.h"

#define FROGGER_CONTENT                                                                                                      \
    "<html><body>Frogger!<table>"                                                                                            \
    "<tr><td/><td>"                                                                                                          \
    "<button id=\"up\">Up</button>"                                                                                          \
    "</td><td/></tr>"                                                                                                        \
    "<tr><td>"                                                                                                               \
    "<button id=\"left\">Left</button>"                                                                                      \
    "</td><td/><td>"                                                                                                         \
    "<button id=\"right\">Right</button>"                                                                                    \
    "</td></tr>"                                                                                                             \
    "<tr><td/><td>"                                                                                                          \
    "<button id=\"down\">Down</button>"                                                                                      \
    "</td><td/></tr>"                                                                                                        \
    "</table></body><script>"                                                                                                \
    "document.getElementById(\"left\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 'a', })};"  \
    "document.getElementById(\"right\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 'd', })};" \
    "document.getElementById(\"up\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 'w', })};"    \
    "document.getElementById(\"down\").onclick = function() {fetch(\"/frogger.html/\", { method: \"POST\", body: 's', })};"  \
    "</script></html>"

int serve_frogger_content(const char *params, char *result, size_t max_result_len)
{

    (void)params;
    // frogger_accept_keypress('d');
    return snprintf(result, max_result_len, FROGGER_CONTENT);
}