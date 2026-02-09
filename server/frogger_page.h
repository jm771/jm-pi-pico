#ifndef FROGGER_PAGE_H
#define FROGGER_PAGE_H

#include <stddef.h>

#define FROGGER_ENDPOINT "/frogger.html"
int serve_frogger_content(const char *params, char *result, size_t max_result_len);

#endif