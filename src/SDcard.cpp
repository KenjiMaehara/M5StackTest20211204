#include <Arduino.h>
#include <M5Stack.h>
#include "menu/menu.h"

String ssidTemp;
String passTemp;

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
 
