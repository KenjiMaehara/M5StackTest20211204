//#include <Arduino.h>
#include <M5Core2.h>
#include "menu/menu.h"
#include "network.h"
#include "aws_iot_mqtt.h"
#include "sound.h"
#include "esp_system.h"


String PUB_TOPIC;
String SUB_TOPIC;


//const int button = 0;         //gpio to use to trigger delay
const int wdtTimeout = 20000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;



#if 1
void IRAM_ATTR resetModule(void) {
  ets_printf("reboot\n");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10); //文字表示の左上位置を設定
  M5.Lcd.setTextSize(5);
  M5.Lcd.print("force restart");
  //M5.Lcd.print(test);
  M5.Lcd.println("");
  delay(5000);  
  esp_restart();
}
#endif
 

void setup() {
  M5.begin(true, true, true, true);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Hello World");
  //M5.Lcd.print("ハロー");



  //pinMode(button, INPUT_PULLUP);                    //init control pin
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer,&resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt

 


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
  printf("\n");

  SUB_TOPIC += AWS_IOT_PUBLISH_TOPIC;
  SUB_TOPIC += "/";
  SUB_TOPIC += conpanyID;
  SUB_TOPIC += "/";
  SUB_TOPIC += "#";
  printf("SUB_TOPIC:  %s\n",SUB_TOPIC.c_str());
  printf("\n");

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


  timerWrite(timer, 0); //reset timer (feed watchdog)

  vTaskDelay(100);

}