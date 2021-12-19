#include <M5Core2.h>
#include "aws_iot_mqtt.h"
#include "time.h"
//#include <DHT.h>
//#include <DHT_U.h>
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "menu/menu.h"
 
 #define TIME_TO_SLEEP  300  // 測定周期（秒）
 

 
 // pin
 #define LED 2
 #define DHTPIN 26
 
 //DHT dht(DHTPIN, DHT11);
 
 WiFiClientSecure net = WiFiClientSecure();
 MQTTClient client = MQTTClient(256);

 int msgReceived = false;
 int msgTFTReceived = false;
 int soundPlayFlag = false;
 
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
 
   client.publish(PUB_TOPIC.c_str(), jsonBuffer);
 }
 
 void messageHandler(String &topic, String &payload) {
    msgReceived = true; 
    msgTFTReceived = true;
    soundPlayFlag = true;
   Serial.println("incoming: " + topic + " - " + payload);
 
 //  StaticJsonDocument<200> doc;
 //  deserializeJson(doc, payload);
 //  const char* message = doc["message"];
 }
 
 void connectAWS()
 {
   //WiFi.mode(WIFI_STA);
   //WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
   Serial.println("Connecting to Wi-Fi");
 
   while (WiFi.status() != WL_CONNECTED){
     delay(500);
     Serial.print(".");
   }
   Serial.println("");
 
   // Configure WiFiClientSecure to use the AWS IoT device credentials
   #if 0
   net.setCACert(AWS_CERT_CA);
   net.setCertificate(AWS_CERT_CRT);
 
    #endif

   net.setCACert(RootCA.c_str());
   net.setCertificate(certificateKey.c_str());
    net.setPrivateKey(privateKey.c_str());


 
   // Connect to the MQTT broker on the AWS endpoint we defined earlier
   //client.begin(AWS_IOT_ENDPOINT, 8883, net);
    client.begin(AWSEndpoint.c_str(), 8883, net);


   // Create a message handler
   client.onMessage(messageHandler);
 
   Serial.print("Connecting to AWS IOT");
 
   while (!client.connect(serialID.c_str())) {
     Serial.print(".");
     delay(100);
   }
 
   if(!client.connected()){
     Serial.println("AWS IoT Timeout!");
     return;
   }
 
   // Subscribe to a topic
   client.subscribe(SUB_TOPIC.c_str());
 
   Serial.println("");
   Serial.println("AWS IoT Connected!");
 }
 

 void AWS_init(void)
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
 
   //publishMessage(88, 99, 00);
   //client.loop();
 
   //digitalWrite(LED, LOW);
   delay(1000);  // MQTTの送信を待つ
 


    #if 0
   // Deep sleepする時間（マイクロ秒）を計算する
   sleeptime = TIME_TO_SLEEP * 1000000 - (millis() - starttime) * 1000 - 1000000;
   esp_deep_sleep(sleeptime);  // DeepSleepモードに移行
   // ここには戻らない
   #endif
 }
 

void vAwsMqttSubTask( void *pvParameters );
void vAwsMqttSubTask02( void *pvParameters );


void AWS_task_init(void)
{

    xTaskCreatePinnedToCore(  vAwsMqttSubTask,       
                "AWS subscribe Task",    
                4096,              
                NULL,              
                4,                 
                NULL, 
                0);


	
    xTaskCreatePinnedToCore(  vAwsMqttSubTask02,     
                "AWS subscribe Task 02", 
                4096,                   
                NULL,                   
                4,                       
                NULL,
                0);
}



int gPubCount = 0;



void vAwsMqttSubTask( void *pvParameters )
{
  while(1)
  {
    #if 1
    if(msgReceived == 1)
    {
//      This code will run whenever a message is received on the SUBSCRIBE_TOPIC_NAME Topic
        delay(100);
        msgReceived = 0;
        printf("testestetsetetwtwtwtwtw");
        Serial.print("Received Message:");
        Serial.println("");
      Serial.println("##############################################");
      gPubCount--;
      //client.loop();
       //connectAWS();
    }
    client.loop();
    #endif

    Serial.println("vAwsMqttSubTask");
    //printf("testestetsetetwtwtwtwtw");

    vTaskDelay(100);
  }
 
}

int test = 0;
int oldTest = 0;


void vAwsMqttSubTask02( void *pvParameters )
{
  while(1)
  {
    M5.update();
    #if 1
    if(msgTFTReceived == 1)
    {
      menu_screen_03();

      M5.Lcd.fillScreen(BLACK);
      delay(2000);
      msgTFTReceived = 0;
    }

    #if 1
    if(test != oldTest)
    {
      oldTest = test;

      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(10, 10); //文字表示の左上位置を設定
      M5.Lcd.setTextSize(3);
      M5.Lcd.print("BtnA wasPressed Test");
      M5.Lcd.print(test);
      M5.Lcd.println("");
      delay(2000);
    }
    #endif



    if (M5.BtnA.wasPressed())
    {
      #if 0
      if(AWSConnectionCheck()==false);
      {
        AWS_init();
        //tryAWSReconnect=false;
      }
      #endif

      if(gPubCount > 3)
      {
        ESP.restart();
      }

      gPubCount++;
      printf("BtnA.wasPressed Test \n");
      //menu_screen_03();
      //M5.Lcd.fillScreen(BLACK);
      //connectAWS();
       Serial.println("");
      publishMessage(88, 99, 00);
      Serial.println("");
      client.loop();
      //digitalWrite(LED, LOW);
      delay(1000);  // MQTTの送信を待つ
      test++;
    }

    //printf("main Loop test\n");


    #endif


      vTaskDelay(100);
  }

}