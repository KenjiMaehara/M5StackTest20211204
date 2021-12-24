#include <Arduino.h>
//#include <M5Stack.h>
#include <M5Core2.h>
#include "menu/menu.h"

String ssidTemp;
String passTemp;
String AWSEndpoint;
String serialID;
String conpanyID;

String RootCA;
String privateKey;
String certificateKey;


void SD_read_forSSID(void)
{
	String str;
	


	if (!SD.begin(4)) 
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
            else if (strstr(d.c_str(),"AWS_ENDPOINT") != NULL)
			{
				AWSEndpoint = d.substring(d.indexOf(":")+1);
			}
            else if (strstr(d.c_str(),"SID") != NULL)
			{
				serialID = d.substring(d.indexOf(":")+1);
			}
            else if (strstr(d.c_str(),"CID") != NULL)
			{
				conpanyID = d.substring(d.indexOf(":")+1);
			}
            else if (strstr(d.c_str(),"#") == 0 || strstr(d.c_str(),"//") == 0 )
			{
				printf("comentOut:  %s\n",d.c_str());
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
    printf("AWS_ENDPOINT:  %s\n",AWSEndpoint.c_str());
    printf("SID:  %s\n",serialID.c_str());
	printf("CID:  %s\n",conpanyID.c_str());

    File RootCAFile = SD.open("/AWS_keys/AmazonRootCA1.pem", FILE_READ);

	while(RootCAFile.available())
	{
		char s = RootCAFile.read();
        RootCA+=s;
    }

    printf("RootCA:  %s\n",RootCA.c_str());



    File certificateFile = SD.open("/AWS_keys/certificate.pem.crt", FILE_READ);

	while(certificateFile.available())
	{
		char s = certificateFile.read();
        certificateKey+=s;
    }

    printf("certificateKey:  %s\n",certificateKey.c_str());


    #if 1
    File privateFile = SD.open("/AWS_keys/private.pem.key", FILE_READ);

	while(privateFile.available())
	{
		char s = privateFile.read();
        privateKey+=s;
    }

    printf("privateKey:  %s\n",privateKey.c_str());
    #endif


	//printf("test:  %s\n",ssidTemp.c_str());
	
	//return str;
}
 
