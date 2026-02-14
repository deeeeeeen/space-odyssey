#ifndef AUDIO_H
#define AUDIO_H
#include "raylib.h"

#define MAX_SIMUL_SOUNDS 5

typedef enum SoundId_e {
    UI_MOVE,
    UI_SELECT,
    ENEMY_KILL,
    SOUND_COUNT
} SoundId;

void AudioInit();
void AudioPlay(SoundId id);
void AudioShutdown();

#endif