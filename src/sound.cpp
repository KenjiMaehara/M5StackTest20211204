//     https://gist.github.com/mongonta0716/18c28bff2dc533d8b51903c939a66a61

#include <Arduino.h>
#include <M5Core2.h>
#include <driver/i2s.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
//#include "AudioGeneratorWAV.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "sound.h"
#include "menu/menu.h"

//AudioGeneratorWAV *wav = NULL;
AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;


//const int I2S_NUM_0 = 0;

#define BCLK_PIN 12
#define LRCK_PIN 0
#define SADTA_PIN 2
#define EXTERNAL_I2S 0
#define OUTPUT_GAIN 80

void sound_init(void)
{
  M5.begin();
  M5.Axp.SetSpkEnable(true);

  file = new AudioFileSourceSD("/mp3/pafu.mp3");
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(I2S_NUM_0, EXTERNAL_I2S); // Output to builtInDAC
  out->SetPinout(BCLK_PIN, LRCK_PIN, SADTA_PIN);
  out->SetOutputModeMono(true);
  out->SetGain((float)OUTPUT_GAIN/100.0);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  //wav = new AudioGeneratorWAV();
	//wav->begin(id3, out);
}



void vSoundTask( void *pvParameters );

void sound_task_init(void)
{

    xTaskCreatePinnedToCore(  vSoundTask,       
                "sound Task",    
                8192,              
                NULL,              
                4,                 
                NULL, 
                1);
}


void vSoundTask( void *pvParameters )
{
  sound_init();

  while(1)
  {
    #if 1

  


    if (mp3->isRunning()) 
    {
      if (!mp3->loop()) mp3->stop();
    }
    else
    {
      if(soundPlayFlag == true)
      {
        sound_init();
      }
      soundPlayFlag = false;
      //Serial.printf("MP3 done\n");
      delay(100);
    }

    #endif
    //vTaskDelay(100);
  }
}
