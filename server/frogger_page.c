#include "frogger.h"
#include "frogger_page.h"
#include "stdio.h"

#define FROGGER_CONTENT "<html><body>Frogger!</body><script>document.getElementById(\"demo\").onclick = function() {myFunction()};function myFunction() { const request = new Request(\"/frogger.html/\", { method: \"POST\", body: '{\"d\": \"d\"}', }); fetch(request).then((response) => { if (response.status !== 200) { throw new Error(\"Something went wrong on API server!\"); } return response; }).catch((error) => { console.error(error); });};</script></html>"

int serve_frogger_content(const char *params, char *result, size_t max_result_len)
{

    (void)params;
    frogger_accept_keypress('d');
    return snprintf(result, max_result_len, FROGGER_CONTENT);
}