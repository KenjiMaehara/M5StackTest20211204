#include <Arduino.h>
#include <M5Stack.h>
#include "menu/menu.h"

void setup() {
  // put your setup code here, to run once:
  M5.begin();

  //Power chipがgpio21, gpio22, I2Cにつながれたデバイスに接続される。
  //バッテリー動作の場合はこの関数を読んでください（バッテリーの電圧を調べるらしい）
  M5.Power.begin();

  M5.Lcd.setBrightness(200); //バックライトの明るさを0（消灯）～255（点灯）で制御
  //M5.Lcd.loadFont("filename", SD); // フォント読み込み
}

void loop() {

  menu1();
  menu_screen_02();
  menu_screen_03();
  menu_screen_04();
  menu_screen_05();
 
  
 
}