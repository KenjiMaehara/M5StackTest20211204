#ifndef __AWS_IOT_MQTT_H_
#define __AWS_IOT_MQTT_H_


//#include <pgmspace.h>
#include <MQTTClient.h>
 
 #define SECRET
 #define THINGNAME "<thing-name>"
 
 //const char WIFI_SSID[] = "<ssid>";
 //const char WIFI_PASSWORD[] = "<wifi-pw>";
 const char AWS_IOT_ENDPOINT[] = "<aws-iot-endpoint>";
 
 // Amazon Root CA 1
 static const char AWS_CERT_CA[] PROGMEM = R"EOF(
 -----BEGIN CERTIFICATE-----
 -----END CERTIFICATE-----
 )EOF";
 
 // Device Certificate
 static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
 -----BEGIN CERTIFICATE-----
 -----END CERTIFICATE-----
 )KEY";
 
 // Device Private Key
 static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
 -----BEGIN RSA PRIVATE KEY-----
 -----END RSA PRIVATE KEY-----
 )KEY";
 

 // The MQTT topics that this device should publish/subscribe
 #define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
 #define AWS_IOT_SUBSCRIBE_TOPIC "esp32/pub/#"

extern void AWS_init(void);
extern int msgReceived;
extern int gPubCount;

extern MQTTClient client;
extern void AWS_task_init(void);
extern int msgTFTReceived;
extern void publishMessage(float temperature, float humidity, int discomfort_index);
extern void connectAWS();



#endif