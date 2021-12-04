#include <pgmspace.h>
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
 


extern void AWS_init(void);
extern int msgReceived;

extern MQTTClient client;
extern void AWS_task_init(void);