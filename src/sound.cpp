//https://gist.github.com/mongonta0716/18c28bff2dc533d8b51903c939a66a61

#include <Arduino.h>
#include <M5Core2.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "sound.h"


AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;


void sound_init(void)
{
  M5.begin();
  M5.Axp.SetSpkEnable(true);

  file = new AudioFileSourceSD("/mp3/chikichiki.mp3");
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 0); // Output to builtInDAC
  out->SetPinout(12, 0, 2);
  out->SetOutputModeMono(true);
  //out->SetGain((float)OUTPUT_GAIN/100.0);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
}