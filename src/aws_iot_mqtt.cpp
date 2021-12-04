#include "aws_iot_mqtt.h"
 #include "time.h"
 //#include <DHT.h>
 //#include <DHT_U.h>
 #include <WiFiClientSecure.h>
 #include <MQTTClient.h>
#include <ArduinoJson.h>
 #include <WiFi.h>
 
 #define TIME_TO_SLEEP  300  // 測定周期（秒）
 
 // The MQTT topics that this device should publish/subscribe
 #define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
 #define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
 
 // pin
 #define LED 2
 #define DHTPIN 26
 
 //DHT dht(DHTPIN, DHT11);
 
 WiFiClientSecure net = WiFiClientSecure();
 MQTTClient client = MQTTClient(256);
 
 #if 0
 int computeDiscomfortIndex(float t, float h)
 {
   int index;
   // see https://ja.wikipedia.org/wiki/%E4%B8%8D%E5%BF%AB%E6%8C%87%E6%95%B0
   // 0.81T+0.01H(0.99T-14.3)+46.3
   index = 0.81f * t + 0.01f * h * (0.99f * t - 14.3f) + 46.3f;
   return index;
 }
 #endif
 
 void publishMessage(float temperature, float humidity, int discomfort_index)
 {
   struct tm timeinfo;
   char now[20];
   if(!getLocalTime(&timeinfo)){
     Serial.println("Failed to obtain time");
     return;
   }
   sprintf(now, "%04d/%02d/%02d %02d:%02d:%02d",
           timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
           timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
 
   StaticJsonDocument<200> doc;
   doc["time"] = now;
   doc["temperature"] = temperature;
   doc["humidity"] = humidity;
   doc["discomfort_index"] = discomfort_index;
   char jsonBuffer[512];
   serializeJson(doc, jsonBuffer); // print to client
 
   client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
 }
 
 void messageHandler(String &topic, String &payload) {
   Serial.println("incoming: " + topic + " - " + payload);
 
 //  StaticJsonDocument<200> doc;
 //  deserializeJson(doc, payload);
 //  const char* message = doc["message"];
 }
 
 void connectAWS()
 {
   WiFi.mode(WIFI_STA);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
   Serial.println("Connecting to Wi-Fi");
 
   while (WiFi.status() != WL_CONNECTED){
     delay(500);
     Serial.print(".");
   }
   Serial.println("");
 
   // Configure WiFiClientSecure to use the AWS IoT device credentials
   net.setCACert(AWS_CERT_CA);
   net.setCertificate(AWS_CERT_CRT);
   net.setPrivateKey(AWS_CERT_PRIVATE);
 
   // Connect to the MQTT broker on the AWS endpoint we defined earlier
   client.begin(AWS_IOT_ENDPOINT, 8883, net);
 
   // Create a message handler
   client.onMessage(messageHandler);
 
   Serial.print("Connecting to AWS IOT");
 
   while (!client.connect(THINGNAME)) {
     Serial.print(".");
     delay(100);
   }
 
   if(!client.connected()){
     Serial.println("AWS IoT Timeout!");
     return;
   }
 
   // Subscribe to a topic
   client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
   Serial.println("");
   Serial.println("AWS IoT Connected!");
 }
 
 void setup0002()
 {
   unsigned long starttime = millis();
   uint64_t sleeptime;
 
   //Serial.begin(115200);
 
   //pinMode(LED, OUTPUT);
   //digitalWrite(LED, HIGH);
   //dht.begin();
   connectAWS();
 
   configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
 
   sleeptime = 2000 - (millis() - starttime) / 1000;
   delay(sleeptime);
   //delay(2000);  // Wait a few seconds between measurements.
   //float h = dht.readHumidity();
   //float t = dht.readTemperature();
   // Check if any reads failed and exit early (to try again).
   //if (isnan(h) || isnan(t)) {
     //Serial.println("Failed to read from DHT sensor!");
     //return;
   //}
   //int di = computeDiscomfortIndex(t, h);
 
    //Serial.printf("Temp: %2.1f, ", t);
   //Serial.printf("Hum: %2.1f, ", h);
   //Serial.printf("DInd: %d", di);
   Serial.println("");
 
   publishMessage(88, 99, 00);
   client.loop();
 
   digitalWrite(LED, LOW);
   delay(1000);  // MQTTの送信を待つ
 
   // Deep sleepする時間（マイクロ秒）を計算する
   sleeptime = TIME_TO_SLEEP * 1000000 - (millis() - starttime) * 1000 - 1000000;
   esp_deep_sleep(sleeptime);  // DeepSleepモードに移行
   // ここには戻らない
 }
 
