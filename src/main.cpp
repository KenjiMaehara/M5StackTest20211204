#include <Arduino.h>
#include <M5Core2.h>
#include "menu/menu.h"
#include "network.h"
#include "aws_iot_mqtt.h"
#include "sound.h"

String PUB_TOPIC;

void setup() {
  M5.begin(true, true, true, true);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Hello World");


  SD_read_forSSID();

  ssid = ssidTemp.c_str();
  password = passTemp.c_str();
	printf("AP_SSID:  %s\n",ssid);
	printf("AP_PASSWORD:  %s\n",password);
	printf("SID:  %s\n",serialID);
	printf("CID:  %s\n",conpanyID);
 
  PUB_TOPIC += AWS_IOT_PUBLISH_TOPIC;
  PUB_TOPIC += "/";
  PUB_TOPIC += conpanyID;
  PUB_TOPIC += "/";
  PUB_TOPIC += serialID;
  //PUB_TOPIC += conpanyID.c_str();
  //PUB_TOPIC += serialID.c_str();
  printf("PUB_TOPIC:  %s\n",PUB_TOPIC.c_str());

  WiFi.begin(ssid, password);
  WiFi.onEvent(WiFiEvent);
  delay(2000);

  AWS_init();
  AWS_task_init();

  //M5.Axp.SetSpkEnable(true); 
  sound_task_init();
  //sound_init();

}

void loop() 
{
  #if 1
  if(msgTFTReceived == 1)
  {
  
    menu_screen_03();

    M5.Lcd.fillScreen(BLACK);
    msgTFTReceived = 0;
  }

  #endif


  delay(100);

}