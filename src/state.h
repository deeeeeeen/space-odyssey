#ifndef STATE_H
#define STATE_H
#include "raylib.h"
#include "main-menu.h"

typedef struct mainmenu_s   mainmenu_t;

enum state_e {
    EXIT = -1,
    TITLE_SCREEN,
    GAME,
    PAUSE
};

typedef struct state_s {
    int                     state;
} state_t;

void UpdateCursor(state_t *statemgr, mainmenu_t *mainmenumgr);
void StartGame(state_t *statemgr, mainmenu_t *mainmenumgr);
void EndGame(state_t *statemgr);

#endif