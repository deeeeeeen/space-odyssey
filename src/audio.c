#include "audio.h"

static Sound sounds[SOUND_COUNT][MAX_SIMUL_SOUNDS];
static int soundalias;

void AudioInit() {
    InitAudioDevice();

    /*
    sounds[UI_MOVE][0] = LoadSound("res/audio/blipSelect.wav");
    sounds[UI_SELECT][0] = LoadSound("res/audio/powerUp.wav");
    sounds[ENEMY_KILL][0] = LoadSound("res/audio/explosion.wav");
    
    for (int sound = 0; sound < SOUND_COUNT; sound++) {
        for (int id = 1; id < MAX_SIMUL_SOUNDS-1; id++) {
            sounds[sound][id] = LoadSoundAlias(sounds[sound][0]);
        }
    }
    soundalias = 0;
    */
}

void AudioPlay(SoundId id) {
    /*
    PlaySound(sounds[id][soundalias]);
    soundalias++;
    if (soundalias >= MAX_SIMUL_SOUNDS) {
        soundalias = 0;
    }
    */
}

void AudioShutdown() {
    CloseAudioDevice();
}