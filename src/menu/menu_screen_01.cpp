#include <Arduino.h>
#include <M5Stack.h>
#include "menu/menu.h"

void menu1(void)
{
M5.Lcd.fillScreen(WHITE);

  
 // 文字描画
  M5.Lcd.setCursor(10, 10); //文字表示の左上位置を設定
  M5.Lcd.setTextColor(RED); //文字色設定(背景は透明)(WHITE, BLACK, RED, GREEN, BLUE, YELLOW...)
  M5.Lcd.setTextSize(2);//文字の大きさを設定（1～7）
  M5.Lcd.print("Hey Guys! \n\n We have a gift for you!");

  M5.Lcd.setTextColor(RED, BLACK); //文字色設定と背景色設定(WHITE, BLACK, RED, GREEN, BLUE, YELLOW...)
  M5.Lcd.setCursor(10, 100); //文字表示の左上位置を設定
  M5.Lcd.print("Hey Guys! \n\n We have a gift for you!");


  delay(1000); // 1000ms待つ
}