#ifndef CUTSCENE_H
#define CUTSCENE_H
#include "raylib.h"
#include "settings.h"
#include "globals.h"
#include "frame.h"
#include "dialogue.h"

#define BAR_HEIGHT                  60
#define SIDEBAR_WIDTH               68

typedef struct str8_s               str8_t;

typedef struct cutscene_s {
    bool                            active;
    bool                            done;
    Rectangle                       top_bar;
    Rectangle                       bottom_bar;
    float                           timer;
    float                           framedelta;
    float                           displacement;
} cutscene_t; 

void InitCutscene(cutscene_t *cutscenemgr);
bool WaitUntilCombatStarts(cutscene_t *cutscenemgr);
void StartCutscene(cutscene_t *cutscenemgr, str8_t *string);
void EndCutscene(cutscene_t *cutscenemgr, str8_t *string);

#endif