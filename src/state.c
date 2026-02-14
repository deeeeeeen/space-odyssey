#include "state.h"

void UpdateMainMenuCursor(state_t *statemgr, mainmenu_t *mainmenumgr) {
    
    if (IsKeyPressed(GetControl(C_MOVE_DOWN))) {
        AudioPlay(UI_MOVE);
        switch ((int)mainmenumgr->cursor_pos.y ) {
            case CURSOR_START_POS:
                mainmenumgr->cursor_pos.y += DIST_BETWEEN_CHOICES;
                break;
            case CURSOR_EXIT_POS:
                mainmenumgr->cursor_pos.y -= DIST_BETWEEN_CHOICES;
                break;
        }
    }
    else if (IsKeyPressed(GetControl(C_MOVE_UP))) {
        AudioPlay(UI_MOVE);
        switch ((int)mainmenumgr->cursor_pos.y) {
            case CURSOR_START_POS:
                mainmenumgr->cursor_pos.y += DIST_BETWEEN_CHOICES;
                break;
            case CURSOR_EXIT_POS:
                mainmenumgr->cursor_pos.y -= DIST_BETWEEN_CHOICES;
                break;
        }
    }

    if (IsKeyPressed(GetControl(C_CONFIRM))) {
        switch ((int)mainmenumgr->cursor_pos.y) {
            case CURSOR_START_POS:
                AudioPlay(UI_SELECT);
                mainmenumgr->pressed_start = true;
                break;
            case CURSOR_EXIT_POS:
                statemgr->state = EXIT;
                break;
        }
    }
}

void UpdatePauseMenuCursor(state_t *statemgr, pause_menu_t *pausemenumgr) {
    
    if (IsKeyPressed(GetControl(C_MOVE_DOWN))) {
        switch ((int)pausemenumgr->cursor_pos.y ) {
            case PM_CURSOR_RESUME_POS:
                pausemenumgr->cursor_pos.y += PM_DIST_BETWEEN_CHOICES;
                break;
            case PM_CURSOR_EXIT_POS:
                pausemenumgr->cursor_pos.y -= PM_DIST_BETWEEN_CHOICES;
                break;
        }
    }
    else if (IsKeyPressed(GetControl(C_MOVE_UP))) {
        switch ((int)pausemenumgr->cursor_pos.y) {
            case PM_CURSOR_RESUME_POS:
                pausemenumgr->cursor_pos.y += PM_DIST_BETWEEN_CHOICES;
                break;
            case PM_CURSOR_EXIT_POS:
                pausemenumgr->cursor_pos.y -= PM_DIST_BETWEEN_CHOICES;
                break;
        }
    }

    if (IsKeyPressed(GetControl(C_CONFIRM))) {
        switch ((int)pausemenumgr->cursor_pos.y) {
            case PM_CURSOR_RESUME_POS:
                statemgr->state = GAME;
                break;
            case PM_CURSOR_EXIT_POS:
                statemgr->state = EXIT;
                break;
        }
    }
}

void StartGame(state_t *statemgr, mainmenu_t *mainmenumgr, player_t *playermgr) {
    if (IsTitleGone(mainmenumgr)) {
        playermgr->in_cutscene.framedelta = FrameGetDelta();
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
    if (IsKeyPressed(GetControl(C_EXIT)) && statemgr->state == GAME) {
        statemgr->state = PAUSE;
    }
    if (playermgr->health <= 0) {
        statemgr->state = EXIT;
    }
}