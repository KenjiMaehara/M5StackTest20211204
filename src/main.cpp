#include <Arduino.h>
#include <M5Stack.h>
#include "menu/menu.h"
#include "network.h"
#include "task.h"
#include "aws_iot_mqtt.h"





void setup() {
  // put your setup code here, to run once:
  M5.begin();

  //Power chipがgpio21, gpio22, I2Cにつながれたデバイスに接続される。
  //バッテリー動作の場合はこの関数を読んでください（バッテリーの電圧を調べるらしい）
  M5.Power.begin();

  M5.Lcd.setBrightness(200); //バックライトの明るさを0（消灯）～255（点灯）で制御
  //M5.Lcd.loadFont("filename", SD); // フォント読み込み
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
  task_init();
}

void loop() {

  #if 0
  menu1();
  menu_screen_02();
  menu_screen_03();
  menu_screen_04();
  menu_screen_05();
  #endif
  delay(100);

}