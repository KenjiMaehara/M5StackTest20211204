#include <Arduino.h>
//#include <M5Stack.h>
#include "menu/menu.h"

void menu_screen_05(void)
{
     M5.Lcd.fillScreen(WHITE);


  // 高度な描画
  for(uint8_t i=0;i<10;i++){
    M5.Lcd.progressBar(0,0,240,20,i*10);//(x,y, width, height, percent)
    delay(100);
  }
  M5.Lcd.qrcode("http://www.m5stack.com",10,10,230,7); //(URL,x,y,size, version)


  delay(1000);// 1000ms待つ
}