#include <Arduino.h>
#include <WiFi.h>

extern const char* ssid;
extern const char* password;

extern void WiFiEvent(WiFiEvent_t event);

extern bool        tryAWSReconnect;
extern bool AWSConnectionCheck(void);