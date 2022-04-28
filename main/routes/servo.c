#include "_routes.h"
#include "driver/ledc.h"
#include "cJSON.h"

static int client_session_id;

void init_servo(void)
{
  ledc_timer_config_t timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_10_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = 50,
      .clk_cfg = LEDC_AUTO_CLK};

  ledc_timer_config(&timer);

  ledc_channel_config_t channel = {
      .gpio_num = 13,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&channel);

  ledc_fade_func_install(0);
  // for (int i = 0; i < 128; i++)
  // {
  //   ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i, 0);
  //   vTaskDelay(10 / portTICK_PERIOD_MS);
  // }
}

int set_angle(int angle)
{
  int dutyMin = 32;
  int dutyMax = 128;
  int dutyrange = dutyMax - dutyMin;
  double dutyIncr = (double)dutyrange / 180;
  int duty = dutyMin + (angle * dutyIncr);

  printf("angle %d equates to duty cycle %d\n", angle, duty);
  ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty, 0);
  return duty;
}

esp_err_t on_servo_url(httpd_req_t *req)
{
  client_session_id = httpd_req_to_sockfd(req);

  httpd_ws_frame_t ws_pkt;
  memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
  ws_pkt.type = HTTPD_WS_TYPE_TEXT;
  ws_pkt.payload = malloc(WS_MAX_SIZE);
  httpd_ws_recv_frame(req, &ws_pkt, WS_MAX_SIZE);
  printf("ws payload: %.*s\n", ws_pkt.len, ws_pkt.payload);
  cJSON *payload = cJSON_ParseWithLength((char *)ws_pkt.payload, ws_pkt.len);
  int angle = cJSON_GetObjectItem(payload, "angle")->valueint;
  cJSON_Delete(payload);
  int duty = set_angle(angle);
  free(ws_pkt.payload);

  cJSON *responce = cJSON_CreateObject();
  cJSON_AddNumberToObject(responce, "angle", angle);
  cJSON_AddNumberToObject(responce, "duty", duty);

  char *responsestr = cJSON_Print(responce);
  cJSON_Delete(responce);

  httpd_ws_frame_t ws_responce = {
      .final = true,
      .fragmented = false,
      .type = HTTPD_WS_TYPE_TEXT,
      .payload = (uint8_t *)responsestr,
      .len = strlen(responsestr)};
  return httpd_ws_send_frame(req, &ws_responce);
  free(responsestr);

  return ESP_OK;
}