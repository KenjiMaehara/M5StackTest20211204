#include <Arduino.h>
#include <M5Stack.h>
#include "menu/menu.h"

void menu_screen_02(void)
{
    M5.Lcd.fillScreen(WHITE);

  

  // ディスプレイの大きさ取得（僕の環境では320 x 240だった）
  int display_width = M5.Lcd.width();
  int display_height = M5.Lcd.height();
  M5.Lcd.setCursor(10, 10); //文字表示の左上位置を設定
  M5.Lcd.printf("w=%d, h=%d",display_width, display_height);


  delay(1000); // 1000ms待つ
}