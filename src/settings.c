#include "settings.h"

static settings settingsmgr;

bool DoesSettingsFileExist() {
    return FileExists(SAVE_PATH);
}

KeyboardKey GetControl(ControlId id) {
    switch (id) {
        case C_EXIT:
            return settingsmgr.controls.exit;
            break;
        case C_PAUSE:
            return settingsmgr.controls.pause;
            break;
        case C_CONFIRM:
            return settingsmgr.controls.confirm;
            break;
        case C_SHOOT:
            return settingsmgr.controls.shoot;
            break;
        case C_MOVE_LEFT:
            return settingsmgr.controls.moveleft;
            break;
        case C_MOVE_RIGHT:
            return settingsmgr.controls.moveright;
            break;
        case C_MOVE_UP:
            return settingsmgr.controls.moveup;
            break;
        case C_MOVE_DOWN:
            return settingsmgr.controls.movedown;
            break;
    }
}

void SetControl(ControlId id, KeyboardKey keyid) {
    switch (id) {
        case C_EXIT:
            settingsmgr.controls.exit = keyid;
            break;
        case C_PAUSE:
            settingsmgr.controls.pause = keyid;
            break;
        case C_CONFIRM:
            settingsmgr.controls.confirm = keyid;
            break;
        case C_SHOOT:
            settingsmgr.controls.shoot = keyid;
            break;
        case C_MOVE_LEFT:
            settingsmgr.controls.moveleft = keyid;
            break;
        case C_MOVE_RIGHT:
            settingsmgr.controls.moveright = keyid;
            break;
        case C_MOVE_UP:
            settingsmgr.controls.moveup = keyid;
            break;
        case C_MOVE_DOWN:
            settingsmgr.controls.movedown = keyid;
            break;
    }
}

float GetDialogueSpeed() {
    return settingsmgr.dialoguespeed;
}

void SetDialogueSpeed(DialogueSpeedId id) {
    switch (id)
    {
    case SLOW_SPEED:
        settingsmgr.dialoguespeed = 0.1f;
        break;
    case NORMAL_SPEED:
        settingsmgr.dialoguespeed = 0.05f;
        break;
    case FAST_SPEED:
        settingsmgr.dialoguespeed = 0.01f;
        break;
    }
}

Vector2 GetWindowResolution() {
    return settingsmgr.windowres;
} 

void InitSettings() {
    if (FileExists(SAVE_PATH)) {
        // TODO: read the file and save it into the settingsmgr struct
    }
    else {
        settingsmgr.windowres = (Vector2) { GetMonitorWidth(GetCurrentMonitor()), 
                                            GetMonitorHeight(GetCurrentMonitor()) 
                                          };
        settingsmgr.controls = (control) { .exit =      KEY_ESCAPE,
                                           .pause =     KEY_ESCAPE,
                                           .confirm =   KEY_ENTER,
                                           .shoot =     KEY_LEFT_CONTROL,
                                           .moveleft =  KEY_LEFT,
                                           .moveright = KEY_RIGHT,
                                           .moveup =    KEY_UP,
                                           .movedown =  KEY_DOWN
                                         };
        settingsmgr.dialoguespeed = 0.05f;
    }
}