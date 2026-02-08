#include "gui.h"

void InitPauseMenu(gui_t *guimgr) {
    guimgr->pause_menu.window_rec = (Rectangle) { 136, 0, 92, 52 };
    guimgr->pause_menu.window_pos = (Vector2) { GAME_WIDTH/2-guimgr->pause_menu.window_rec.width/2, GAME_HEIGHT/2-guimgr->pause_menu.window_rec.height/2};

    guimgr->pause_menu.cursor_rec = (Rectangle) { 136, 52, 8, 7 };
    guimgr->pause_menu.cursor_pos = (Vector2) { guimgr->pause_menu.window_pos.x+14-8, PM_CURSOR_RESUME_POS };
}

void InitSidebar(gui_t *guimgr) {
    guimgr->sidebars.base = (Rectangle) { 68.f, 0.f, 68.f, 320.f };
    guimgr->sidebars.frame = (Rectangle) { 0.f, 0.f, 68.f, 320.f };

    guimgr->sidebars.base_pos_left =   (Vector2) { ZERO, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
    guimgr->sidebars.base_pos_right =  (Vector2) { GAME_WIDTH-guimgr->sidebars.base.width, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
    guimgr->sidebars.frame_pos_left =  (Vector2) { ZERO, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
    guimgr->sidebars.frame_pos_right = (Vector2) { GAME_WIDTH-guimgr->sidebars.base.width, -(guimgr->sidebars.base.height-GAME_HEIGHT) };
}

void InitGui(gui_t *guimgr) {
    guimgr->spritemap = LoadTexture("res/gui.png");
    InitSidebar(guimgr);
    InitPauseMenu(guimgr);
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