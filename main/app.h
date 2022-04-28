#ifndef app_h
#define app_h

#include "esp_err.h"
#define WS_MAX_SIZE 1024

esp_err_t send_ws_message(char *message);
esp_err_t send_ws_message_to_clinet(char *message, int clinet_id);
#endif