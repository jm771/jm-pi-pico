#include <stddef.h>
#include "server_utils.h"

#ifndef CSS_H
#define CSS_H

#define STYLES_ENDPOINT "/styles.css"

void serve_css(const char *params, TCP_RESPONSE_T *result);

#endif