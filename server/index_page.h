#ifndef INDEX_PAGE_H
#define INDEX_PAGE_H

#include "stddef.h"

#define INDEX_ENDPOINT "/index.html"
int serve_test_server_content(const char *params, char *result, size_t max_result_len);
int index_age_init(uint32_t *selectedProgramRef, band_settings_t *bandSettingsRef)
{
    selectedProgram = selectedProgramRef;
    bandSettings = bandSettingsRef;

#endif