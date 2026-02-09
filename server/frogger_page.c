#include "frogger.h"
#include "frogger_page.h"

#define FROGGER_CONTENT "<html><body>Frogger!</body></html>"

int serve_frogger_content(const char *params, char *result, size_t max_result_len)
{

    (void)params;
    frogger_accept_keypress('d');
    return snprintf(result, max_result_len, FROGGER_CONTENT);
}