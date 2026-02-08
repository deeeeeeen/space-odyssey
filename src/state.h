#ifndef STATE_H
#define STATE_H
#include "raylib.h"
#include "player.h"
#include "gui.h"
#include "main-menu.h"

typedef struct mainmenu_s   mainmenu_t;
typedef struct gui_s        gui_t;
typedef struct player_s     player_t;

enum state_e {
    EXIT = -1,
    TITLE_SCREEN,
    GAME,
    PAUSE
};

typedef struct state_s {
    int                     state;
    RenderTexture2D         pause_tex;
} state_t;

void UpdateMainMenuCursor(state_t *statemgr, mainmenu_t *mainmenumgr);
void UpdatePauseMenuCursor(state_t *statemgr, pause_menu_t *pausemenumgr);
void StartGame(state_t *statemgr, mainmenu_t *mainmenumgr, player_t *playermgr);
void EndGame(state_t *statemgr, player_t *playermgr);

#endif