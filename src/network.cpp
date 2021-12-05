#include <Arduino.h>
#include <WiFi.h>
#include "network.h"

const char* ssid       = "20200815me";   //YOUR_SSID:
const char* password   = "0815asdf";   //YOUR_PASS:

bool        ap_connect = false;

void WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        ap_connect = false;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        ap_connect = true;
        break;
    default:
        break;
    }
}
