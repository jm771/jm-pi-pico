#ifndef SERVER_H
#define SERVER_H

#include "band_controler.h"

void server_poll();
int server_init(uint32_t *selectedProgram, band_settings_t const *settingsRef);

#ifdef WIFI_SUPPORTED
void handle_post_request(const char *request, TCP_RESPONSE_T *result);

void handle_server_request(const char *request, const char *params, TCP_RESPONSE_T *result);

#endif



#endif