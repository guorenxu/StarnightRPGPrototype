#ifndef _DXAUDIO_H
#define _DXAUDIO_H

#include "dsutil.h"

extern CSoundManager *dsound;

int Init_DirectSound(HWND);
CSound *LoadSound(char *);
void PlaySound(CSound *);
void LoopSound(CSound *);
void StopSound(CSound *);


#endif