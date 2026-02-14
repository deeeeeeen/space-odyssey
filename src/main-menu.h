#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "raylib.h"
#include "globals.h"
#include "frame.h"

#define MAIN_MENU_SPRITE_PATH       (const char*)"res/graphic/main-menu.png"
#define CURSOR_START_POS            226
#define CURSOR_EXIT_POS             CURSOR_START_POS+20
#define DIST_BETWEEN_CHOICES        20

typedef struct mainmenu_s {
    Texture2D                       sprite;
    Rectangle                       title_rec;
    Vector2                         title_pos;
    Rectangle                       choices_rec;
    Vector2                         choices_pos;
    Rectangle                       cursor_rec;
    Vector2                         cursor_pos;
    Rectangle                       credits_rec;
    Vector2                         credits_pos;
    float                           frametime;
    float                           timer;
    bool                            pressed_start;
    Color                           textcolor;
} mainmenu_t;

void InitMainMenu(mainmenu_t *menumgr);
void DrawMainMenu(mainmenu_t *menumgr);
void FadeAwayTitle(mainmenu_t *menumgr);
bool IsTitleGone(mainmenu_t *menumgr);

#endif