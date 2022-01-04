#ifndef __MENU_H_
#define __MENU_H_


#include <Arduino.h>
//#include <M5Stack.h>


extern void menu1(void);
extern void menu_screen_02(void);
extern void menu_screen_03(void);
extern void menu_screen_04(void);
extern void menu_screen_05(void);
extern void SD_read_forSSID(void);

extern String ssidTemp;
extern String passTemp;
extern String serialID;
extern String conpanyID;

extern String PUB_TOPIC;
extern String SUB_TOPIC;


extern String RootCA;
extern String privateKey;
extern String certificateKey;


extern String AWSEndpoint;

extern int soundPlayFlag;
extern void setup_TFT(void);
extern void TFT_test();

extern int gAWSpublish;

#endif