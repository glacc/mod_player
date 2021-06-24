#ifndef MODPLAYREV2_H
#define MODPLAYREV2_H

#define SMP_RATE 44100

#include <stdint.h>

bool MPLoadModule(uint8_t *SongDataOrig, uint32_t SongDataLeng, bool UsingInterpolation, bool IsSTK = false, float TargetStereoSep = 0);
char *MPGetSongName();
uint32_t MPGetPos();
bool MPPlayModule();
void MPPlayPause();
void MPSetPos(uint8_t Pos);
void MPSetVolume(uint8_t Volume);
void MPResetModule();
bool MPStopModule();
double MPGetExcuteTime();

#endif
