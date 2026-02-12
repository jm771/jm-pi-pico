#ifndef FROGGER_PAGE_H
#define FROGGER_PAGE_H

#include <stddef.h>
#include "server_utils.h"

#define FROGGER_ENDPOINT "frogger.html"
void serve_frogger_content(const char *params, TCP_RESPONSE_T *result);

#endif