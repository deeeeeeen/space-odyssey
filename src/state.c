#include "state.h"

void UpdateCursor(state_t *statemgr, mainmenu_t *mainmenumgr) {
    
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        switch ((int)mainmenumgr->cursor_pos.y ) {
            case CURSOR_START_POS:
                mainmenumgr->cursor_pos.y += DIST_BETWEEN_CHOICES;
                break;
            case CURSOR_EXIT_POS:
                mainmenumgr->cursor_pos.y -= DIST_BETWEEN_CHOICES;
                break;
        }
    }
    else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        switch ((int)mainmenumgr->cursor_pos.y) {
            case CURSOR_START_POS:
                mainmenumgr->cursor_pos.y += DIST_BETWEEN_CHOICES;
                break;
            case CURSOR_EXIT_POS:
                mainmenumgr->cursor_pos.y -= DIST_BETWEEN_CHOICES;
                break;
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        switch ((int)mainmenumgr->cursor_pos.y) {
            case CURSOR_START_POS:
                mainmenumgr->pressed_start = true;
                break;
            case CURSOR_EXIT_POS:
                statemgr->state = EXIT;
                break;
        }
    }
}

void StartGame(state_t *statemgr, mainmenu_t *mainmenumgr) {
    if (IsTitleGone(mainmenumgr)) {
        statemgr->state = GAME;
    }
}

void EndGame(state_t *statemgr) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        statemgr->state = EXIT;
    }
}