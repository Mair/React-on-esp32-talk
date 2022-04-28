#include "_routes.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// static char *TAG = "magnetometer";

uint32_t hall_sens_read();

int client_session_id;
static TaskHandle_t hall_task = NULL;

// typedef struct client_sessions_t
// {
//   session_id;
// } client_sessions_t;

void readHall(void *params)
{
  int *interville_ptr = (int *)params;
  int interville = *interville_ptr;
  printf("interville %d\n", interville);
  while (true)
  {
    uint32_t read = hall_sens_read();
    printf("hall read %d\n", read);
    cJSON *hall_payload = cJSON_CreateObject();
    cJSON_AddNumberToObject(hall_payload, "val", read);
    char *payload_str = cJSON_Print(hall_payload);
    send_ws_message_to_clinet(payload_str, client_session_id);
    cJSON_Delete(hall_payload);
    free(payload_str);
    vTaskDelay(pdMS_TO_TICKS(interville));
  }
}

esp_err_t on_magnetometer(httpd_req_t *req)
{
  client_session_id = httpd_req_to_sockfd(req);
  if (req->method == HTTP_GET)
    return ESP_OK;

  printf("data client_session_id %d, len:%d\n", client_session_id, req->content_len);
  httpd_ws_frame_t ws_pkt;
  memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
  ws_pkt.type = HTTPD_WS_TYPE_TEXT;
  ws_pkt.payload = malloc(WS_MAX_SIZE);
  httpd_ws_recv_frame(req, &ws_pkt, WS_MAX_SIZE);
  printf("ws payload: %.*s\n", ws_pkt.len, ws_pkt.payload);
  cJSON *cmd_payload = cJSON_Parse((char *)ws_pkt.payload);
  if (cmd_payload == NULL)
  {
    printf("error\n");
    // handle error
  }
  if (strcmp(cJSON_GetObjectItem(cmd_payload, "cmd")->valuestring, "start") == 0)
  {
    printf("cmd start\n");
    if (hall_task == NULL)
    {
      int interville = cJSON_GetObjectItem(cmd_payload, "interval")->valueint;
      printf("create task\n");
      xTaskCreate(readHall, "readHall", 1024 * 4, &interville, 5, &hall_task);
    }
  }
  if (strcmp(cJSON_GetObjectItem(cmd_payload, "cmd")->valuestring, "stop") == 0)
  {
    if (hall_task != NULL)
    {
      vTaskDelete(hall_task);
      hall_task = NULL;
    }
  }
  free(ws_pkt.payload);

  char *response = "connected OK 😊";
  httpd_ws_frame_t ws_responce = {
      .final = true,
      .fragmented = false,
      .type = HTTPD_WS_TYPE_TEXT,
      .payload = (uint8_t *)response,
      .len = strlen(response)};
  return httpd_ws_send_frame(req, &ws_responce);
}
