#include "_routes.h"

esp_err_t on_hello_world(httpd_req_t *req)
{
  httpd_resp_sendstr(req, "hello world 👋👋👋 😁");
  return ESP_OK;
}