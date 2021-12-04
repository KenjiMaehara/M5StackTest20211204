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
  
 
  
  M5.Lcd.fillScreen(WHITE);


  // 高度な描画
  for(uint8_t i=0;i<10;i++){
    M5.Lcd.progressBar(0,0,240,20,i*10);//(x,y, width, height, percent)
    delay(100);
  }
  M5.Lcd.qrcode("http://www.m5stack.com",10,10,230,7); //(URL,x,y,size, version)


  delay(1000);// 1000ms待つ
}