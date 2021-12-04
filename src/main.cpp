#include <Arduino.h>
#include <M5Stack.h>
#include "menu/menu.h"



void SD_read_forSSID(void)
{
	String str;
	


	if (!SD.begin()) 
    {
        Serial.println("SD initialization failed!\n");
        return;
    }

    if (SD.exists("SSID.txt")) 
    {
        Serial.println("env.bin doesn't exist.\n");
    }

     
    Serial.println("SD initialization done.\n");

    //File envFile = SD.open("env.bin", FILE_READ);
	File ssidFile = SD.open("/SSID.txt", FILE_READ);

    //envFile.read(&hdrEnv,sizeof(env_hdr_t));
    //envFile.read(&Env,sizeof(env_hdr_t));


	String d;
	String ssidTemp;
	String passTemp;

	while(ssidFile.available())
	{
		char s=ssidFile.read();
		if(s=='\r')
		{
			d.trim();

			if (strstr(d.c_str(),"SSID") != NULL)
			{
				ssidTemp = d.substring(d.indexOf(":")+1);
			}
			else if (strstr(d.c_str(),"PASSWORD") != NULL)
			{
				passTemp = d.substring(d.indexOf(":")+1);
			}

			d="";
		}
		else
		{
			d+=s;
		}
	}

	
    ssidFile.close();


	printf("SSID:  %s\n",ssidTemp.c_str());
	printf("PASSWORD:  %s\n",passTemp.c_str());

	//printf("test:  %s\n",ssidTemp.c_str());
	
	//return str;
}
 





void setup() {
  // put your setup code here, to run once:
  M5.begin();

  //Power chipがgpio21, gpio22, I2Cにつながれたデバイスに接続される。
  //バッテリー動作の場合はこの関数を読んでください（バッテリーの電圧を調べるらしい）
  M5.Power.begin();

  M5.Lcd.setBrightness(200); //バックライトの明るさを0（消灯）～255（点灯）で制御
  //M5.Lcd.loadFont("filename", SD); // フォント読み込み
  SD_read_forSSID();
}

void loop() {

  menu1();
  menu_screen_02();
  menu_screen_03();
  menu_screen_04();
  menu_screen_05();
 
  
 
}