#include "_routes.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "app.h"

#define BTN 12

static xSemaphoreHandle btn_sem;
static int client_session_id;

static void IRAM_ATTR on_btn_pushed(void *args)
{
  xSemaphoreGiveFromISR(btn_sem, NULL);
}

static void btn_push_task(void *params)
{
  while (true)
  {
    xSemaphoreTake(btn_sem, portMAX_DELAY);
    cJSON *payload = cJSON_CreateObject();
    cJSON_AddBoolToObject(payload, "btn_state", gpio_get_level(BTN));
    char *message = cJSON_Print(payload);
    printf("message: %s\n", message);
    send_ws_message_to_clinet(message, client_session_id);
    cJSON_Delete(payload);
    free(message);
  }
}

void init_btn(void)
{

  btn_sem = xSemaphoreCreateBinary();
  xTaskCreate(btn_push_task, "btn_push_task", 2048, NULL, 5, NULL);
  gpio_pad_select_gpio(BTN);
  gpio_set_direction(BTN, GPIO_MODE_INPUT);
  gpio_set_intr_type(BTN, GPIO_INTR_ANYEDGE);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(BTN, on_btn_pushed, NULL);
}

esp_err_t on_web_socket_btn_push_url(httpd_req_t *req)
{
  client_session_id = httpd_req_to_sockfd(req);
  if (req->method == HTTP_GET)
    return ESP_OK;

  httpd_ws_frame_t ws_pkt;
  memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
  ws_pkt.type = HTTPD_WS_TYPE_TEXT;
  ws_pkt.payload = malloc(WS_MAX_SIZE);
  httpd_ws_recv_frame(req, &ws_pkt, WS_MAX_SIZE);
  printf("ws payload: %.*s\n", ws_pkt.len, ws_pkt.payload);
  free(ws_pkt.payload);

  char *response = "{\"message\": \"Ready for button push 🔽 😊\"}";
  httpd_ws_frame_t ws_responce = {
      .final = true,
      .fragmented = false,
      .type = HTTPD_WS_TYPE_TEXT,
      .payload = (uint8_t *)response,
      .len = strlen(response)};
  return httpd_ws_send_frame(req, &ws_responce);
}