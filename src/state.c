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

void StartGame(state_t *statemgr, mainmenu_t *mainmenumgr, player_t *playermgr) {
    if (IsTitleGone(mainmenumgr)) {
        playermgr->in_cutscene.framedelta = GetFrameTime();
        if (playermgr->pos.y > GAME_HEIGHT-PLAYER_HEIGHT-1) {
            playermgr->pos.y -= 30*playermgr->in_cutscene.framedelta;
        }
        else if (playermgr->pos.y <= GAME_HEIGHT-PLAYER_HEIGHT-1) {
            playermgr->pos.y = GAME_HEIGHT-PLAYER_HEIGHT-1;
            playermgr->in_cutscene.timer += playermgr->in_cutscene.framedelta;
            if (playermgr->in_cutscene.timer >= 1) {
                playermgr->in_cutscene.timer = 0;
                statemgr->state = GAME;
            }
        }
    }
}

void EndGame(state_t *statemgr, player_t *playermgr) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        statemgr->state = EXIT;
    }
    if (playermgr->health <= 0) {
        statemgr->state = EXIT;
    }
}