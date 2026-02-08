#include "gui.h"

void InitSidebar(gui_t *guimgr) {
    guimgr->sidebars.sprite = LoadTexture("res/gui.png");
    guimgr->sidebars.base = (Rectangle) { 68.f, 0.f, 68.f, 320.f };
    guimgr->sidebars.frame = (Rectangle) { 0.f, 0.f, 68.f, 320.f };

    guimgr->sidebars.base_pos_left =   (Vector2) { ZERO, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
    guimgr->sidebars.base_pos_right =  (Vector2) { GAME_WIDTH-guimgr->sidebars.base.width, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
    guimgr->sidebars.frame_pos_left =  (Vector2) { ZERO, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
    guimgr->sidebars.frame_pos_right = (Vector2) { GAME_WIDTH-guimgr->sidebars.base.width, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
}

void UpdateSidebar(gui_t *guimgr) {
    guimgr->sidebars.framedelta = GetFrameTime();

    guimgr->sidebars.displacement += 30*guimgr->sidebars.framedelta;
    if (guimgr->sidebars.displacement >= 32) {
        guimgr->sidebars.displacement = 0;
    }

    guimgr->sidebars.base_pos_left.y = -(guimgr->sidebars.base.height-GAME_HEIGHT)+guimgr->sidebars.displacement;
    guimgr->sidebars.base_pos_right.y = -(guimgr->sidebars.base.height-GAME_HEIGHT)+guimgr->sidebars.displacement;
}