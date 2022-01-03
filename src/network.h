#ifndef __NETWORK_H_
#define __NETWORK_H_

#include <Arduino.h>
#include <WiFi.h>

extern const char* ssid;
extern const char* password;

extern void WiFiEvent(WiFiEvent_t event);

extern bool        tryAWSReconnect;
extern bool AWSConnectionCheck(void);


#endif