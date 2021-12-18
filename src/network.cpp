#include <M5Core2.h>
#include <Arduino.h>
#include <WiFi.h>
#include "network.h"

const char* ssid       = "20200815me";   //YOUR_SSID:
const char* password   = "0815asdf";   //YOUR_PASS:

bool        ap_connect = false;
bool        tryAWSReconnect = false;

void WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        #if 0
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(10, 10); //文字表示の左上位置を設定
        M5.Lcd.setTextSize(3);
        M5.Lcd.println(WiFi.localIP());
        M5.Lcd.print("WiFi connected");
        #endif
        ap_connect = false;
        //tryAWSReconnect = true;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        ap_connect = true;
        break;
    default:
        break;
    }
}
