#include <Arduino.h>
#include <M5Stack.h>
#include "menu/menu.h"

void menu_screen_03(void)
{
    M5.Lcd.fillScreen(WHITE);

  
  // 特定の色で全体を塗りつぶす
  uint16_t colors[] = {WHITE, RED, GREEN, BLUE, BLACK, YELLOW };
  for(int j = 0; j<6; j++){
    M5.Lcd.fillScreen(colors[j]);
    delay(300);
  }

   uint16_t colorvalue;
   colorvalue= M5.Lcd.color565(123,30,50); //RGB値（0～255）を指定することもできる
   M5.Lcd.fillScreen(colorvalue);


  delay(1000);// 1000ms待つ
}