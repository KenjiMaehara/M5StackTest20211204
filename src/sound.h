#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include <driver/i2s.h>
//#include "AudioGeneratorWAV.h"



extern void sound_init(void);
extern void sound_task_init(void);

//extern AudioGeneratorWAV *wav;
extern AudioGeneratorMP3 *mp3;
extern AudioFileSourceSD *file;
extern AudioOutputI2S *out;
extern AudioFileSourceID3 *id3;