#include <ArduinoOTA.h>
#define LED_BUILTIN 2
#include "wifi_credentials.h"

void setup() {
  Serial.begin(115200);
  Serial.printf("Started up\n");

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname("esp_test");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
      Serial.println("Started updating: " + type);
    })
    .onEnd([]() {
      Serial.println("Update complete");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      unsigned int percent = progress / (total / 100);
      digitalWrite(2, (percent % 2) == 1 ? HIGH : LOW);
      Serial.printf("Progress: %u%%\n", percent);
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR)
        Serial.printf("Auth Faile\n");
      else if (error == OTA_BEGIN_ERROR)
        Serial.printf("Begin Failed\n");
      else if (error == OTA_CONNECT_ERROR)
        Serial.printf("Connect Failed\n");
      else if (error == OTA_RECEIVE_ERROR)
        Serial.printf("Receive Failed\n");
      else if (error == OTA_END_ERROR)
        Serial.printf("End Failed\n");
    });

  ArduinoOTA.begin();
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
  ArduinoOTA.handle();
}
