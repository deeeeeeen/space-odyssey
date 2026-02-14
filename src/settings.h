#ifndef SETTINGS_H
#define SETTINGS_H
#include "raylib.h"

#define SAVE_PATH (const char*)"sav/game.sav"

typedef struct game_s   game_t;

typedef enum {
    C_EXIT,
    C_PAUSE,
    C_CONFIRM,
    C_SHOOT,
    C_MOVE_LEFT,
    C_MOVE_RIGHT,
    C_MOVE_UP,
    C_MOVE_DOWN
} ControlId;

typedef enum {
    SLOW_SPEED,
    NORMAL_SPEED,
    FAST_SPEED,
} DialogueSpeedId;

typedef struct {
    KeyboardKey exit;
    KeyboardKey pause;
    KeyboardKey confirm;
    KeyboardKey shoot;
    KeyboardKey moveleft;
    KeyboardKey moveright;
    KeyboardKey moveup;
    KeyboardKey movedown;
} control;

typedef struct {
    Vector2 windowres;
    control controls;
    float   dialoguespeed;
} settings;

bool DoesSettingsFileExist();
KeyboardKey GetControl(ControlId id);
void SetControl(ControlId id, KeyboardKey keyid);
float GetDialogueSpeed();
void SetDialogueSpeed(DialogueSpeedId id);
Vector2 GetWindowResolution();
void InitSettings();

#endif