#ifndef INDEX_PAGE_H
#define INDEX_PAGE_H

#include "stddef.h"
#include "band_controler.h"
#include "server_utils.h"

#define INDEX_ENDPOINT "/index.html"
void serve_index_content(const char *params, TCP_RESPONSE_T *result);
void index_page_init(uint32_t *selectedProgramRef, band_settings_t *bandSettingsRef);
void set_band_enabled(bool enabled);
#endif