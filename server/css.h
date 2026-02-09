#include <stddef.h>

#ifndef CSS_H
#define CSS_H

#define STYLES_ENDPOINT "/styles.css"

int serve_css(const char *params, char *result, size_t max_result_len);

#endif