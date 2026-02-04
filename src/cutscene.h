#ifndef CUTSCENE_H
#define CUTSCENE_H
#include "raylib.h"

#define GAME_WIDTH                  512
#define GAME_HEIGHT                 288

typedef struct render_s             render_t;
typedef struct player_s             player_t;
typedef struct frame_s              frame_t;
typedef struct projectilegroup_s    projectilegroup_t;

typedef struct cutscene_s {
    Rectangle                       top_bar;
    Rectangle                       bottom_bar;
    float                           timer;
    float                           framedelta;
    float                           displacement;
} cutscene_t; 

void InitCutscene(cutscene_t *cutscenemgr);
void StartCutscene(cutscene_t *cutscenemgr);
void EndCutscene(cutscene_t *cutscenemgr);

#endif