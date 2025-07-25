#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMAC[] = {0xA0, 0x20, 0xA6, 0x23, 0xDF, 0x64};
const int numValues = 5;
uint16_t analogValues[numValues];
uint16_t receivedValues[numValues];    

//sender
/*

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  if (Serial.available() >= numValues * 2) {
    // Read bytes into the analogValues array
    for (int i = 0; i < numValues; i++) {
      uint8_t lowByte = Serial.read();
      uint8_t highByte = Serial.read();
      analogValues[i] = (highByte << 8) | lowByte;  // little-endian
    }

    // Send the analogValues array as raw bytes via ESP-NOW
    esp_now_send(receiverMAC, (uint8_t *)analogValues, sizeof(analogValues));
  }
}*/

//Reciever

void onReceive(uint8_t *mac, uint8_t *data, uint8_t len) {
  if (len == numValues * 2) {  
    for (int i = 0; i < numValues; i++) {
      uint8_t low = data[i * 2];
      uint8_t high = data[i * 2 + 1];
      receivedValues[i] = low | (high << 8);
    }

    // Forward received data to Arduino over Serial as raw bytes
    for (int i = 0; i < numValues; i++) {
      Serial.write(receivedValues[i] & 0xFF);         // low byte
      Serial.write((receivedValues[i] >> 8) & 0xFF);  // high byte
    }
  }
}

void setup() {
  Serial.begin(4800);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onReceive);
  
}

void loop() {
  
}
