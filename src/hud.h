#ifndef HUD_H
#define HUD_H
#include "raylib.h"
#include "frame.h"
#include "globals.h"

#define HUD_SPRITE_PATH "res/graphic/hud.png"

typedef struct hud_s {
    Texture2D       sprite;
    Vector2         hp_box_size;
    Rectangle       hp_rec;
    Vector2         hp_pos;
    // ---
    Vector2         time_box_size;
    Rectangle       time_rec;
    Vector2         time_pos;
    int             playtime_s;
    // ---
    Vector2         lvl_box_size;
    Rectangle       lvl_rec;
    Vector2         lvl_pos;
    // ---
    Vector2         score_box_size;
    Rectangle       score_rec;
    Vector2         score_pos;
    int             score;

    float           framedelta;
    float           timer;
} hud_t;

void UpdateHud(hud_t *hudmgr);
void InitHud(hud_t *hudmgr);

#endif