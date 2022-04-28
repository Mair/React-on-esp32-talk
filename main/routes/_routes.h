#ifndef routes_h
#define routes_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cJSON.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "../app.h"

/******************** init function ****************/
void init_btn(void);
void init_led(void);
void init_servo(void);

/******************** http callbacks ****************/
esp_err_t on_toggle_led_url(httpd_req_t *req);
esp_err_t on_hello_world(httpd_req_t *req);
esp_err_t on_magnetometer(httpd_req_t *req);
esp_err_t on_web_socket_btn_push_url(httpd_req_t *req);
esp_err_t on_servo_url(httpd_req_t *req);
/**************************************************/
void toggle_led(bool is_on);

#endif