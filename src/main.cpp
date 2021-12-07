//#include <Arduino.h>
#include <M5Core2.h>
#include "menu/menu.h"
#include "network.h"
#include "aws_iot_mqtt.h"
#include "sound.h"


void setup() {
  M5.begin(true, true, true, true);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Hello World");


  SD_read_forSSID();

  ssid = ssidTemp.c_str();
  password = passTemp.c_str();
	printf("AP_SSID:  %s\n",ssid);
	printf("AP_PASSWORD:  %s\n",password);


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