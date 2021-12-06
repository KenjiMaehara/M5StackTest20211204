//https://gist.github.com/mongonta0716/18c28bff2dc533d8b51903c939a66a61


#include <M5Core2.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"


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

}