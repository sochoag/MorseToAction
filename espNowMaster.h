#ifndef espNowMaster_h
#define espNowMaster_h
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xCC, 0xDB, 0xA7, 0x12, 0x7B, 0xA4};

typedef struct struct_message
{
  byte accion;
} struct_message;

struct_message Send;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setupEspNow()
{
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

void sendEspNow()
{
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&Send, sizeof(Send));
  if (result == ESP_OK)
  {
    Serial.println("Sent with success");
  }
  else
  {
    Serial.println("Error sending the data");
  }
  delay(500);
}

#endif
