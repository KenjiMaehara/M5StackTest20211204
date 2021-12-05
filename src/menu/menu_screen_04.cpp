#include <Arduino.h>
//#include <M5Stack.h>
#include <M5Core2.h>
#include "menu/menu.h"

void menu_screen_04(void)
{
    M5.Lcd.fillScreen(WHITE);

  // 図形を書く（長方形、円、三角形）
  M5.Lcd.drawRect(10, 10, 80, 50, BLUE); //枠だけ left, top, witdh, height
  M5.Lcd.fillRect(15, 15, 70, 40, RED); // 塗りつぶし left, top, witdh, height

  M5.Lcd.drawRoundRect(1000, 10, 80, 50, 10, GREEN); // 隅が丸くなった長方形(x,y,width,height,radius,col)
  
  M5.Lcd.drawCircle(250, 50, 40, BLUE); //枠だけ center-x, center-y, radius
  M5.Lcd.fillCircle(250, 50, 30, RED); //塗りつぶし center-x, center-y, radius
  
  M5.Lcd.drawTriangle(50, 130, 100, 130, 80,  200, BLUE);//枠だけ (x1, y1), (x2,y2), (x3, y3)
  M5.Lcd.fillTriangle(90, 130, 130, 150, 110, 200, RED);//塗りつぶし (x1, y1), (x2,y2), (x3, y3)

  M5.Lcd.drawPixel(300, 40, RED);//（x, y)のピクセルを指定の色で塗る
  M5.Lcd.drawPixel(300, 45, RED);//（x, y)のピクセルを指定の色で塗る
  M5.Lcd.drawPixel(300, 50, RED);//（x, y)のピクセルを指定の色で塗る
  M5.Lcd.drawPixel(300, 55, RED);//（x, y)のピクセルを指定の色で塗る
  
  M5.Lcd.drawLine(0, 0, 120, 120, BLACK);//（x1, y1) (x2, y2)
  M5.Lcd.drawFastVLine(150, 110, 100, RED);//(x,y,height,col) (x,y)からheightだけ垂直（Vertical）な線を書く
  M5.Lcd.drawFastHLine(150, 110, 150, GREEN);//(x,y,width,col) (x,y)からwidthだけ水平（Horizontal）な線を書く


  delay(1000);// 1000ms待つ
}