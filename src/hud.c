#include "hud.h"

void InitHud(hud_t *hudmgr) {
    hudmgr->sprite = LoadTexture(HUD_SPRITE_PATH);

    hudmgr->hp_pos = (Vector2) { 30, 33 };
    hudmgr->hp_box_size = (Vector2) { 8, 10 };
    hudmgr->hp_rec = (Rectangle) { 0, 14, 8, 7 };

    hudmgr->time_pos = (Vector2) { 450, 4 };
    hudmgr->time_box_size = (Vector2) { 56, 10 };
    hudmgr->time_rec = (Rectangle) { 0, 0, 8, 7 };

    hudmgr->lvl_pos = (Vector2) { 450, 14 };
    hudmgr->lvl_box_size = (Vector2) { 56, 10 };
    hudmgr->lvl_rec = (Rectangle) { 0, 7, 32, 7 };

    hudmgr->score_pos = (Vector2) { 450, 30 };
    hudmgr->score_box_size = (Vector2) { 56, 20 };
    hudmgr->score_rec = (Rectangle) { 32, 7, 48, 7 };
}