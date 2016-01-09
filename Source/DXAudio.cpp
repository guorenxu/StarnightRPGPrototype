#include "dxaudio.h"

CSoundManager *dsound;

int Init_DirectSound(HWND hwnd)
{
    HRESULT result;

    dsound = new CSoundManager();

    result = dsound->Initialize(hwnd, DSSCL_PRIORITY);

    result = dsound->SetPrimaryBufferFormat(2, 22050, 16);

    return 1;
}

CSound *LoadSound(char *filename)
{
    HRESULT result;

    CSound *wave;

    result = dsound->Create(&wave, filename);

    return wave;
}

void PlaySound(CSound *sound)
{
    sound->Play();
}

void LoopSound(CSound *sound)
{
    sound->Play(0, DSBPLAY_LOOPING);
}

void StopSound(CSound *sound)
{
    sound->Stop();
}