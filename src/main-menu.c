#include "main-menu.h"

void InitMainMenu(mainmenu_t *menumgr) {
    menumgr->sprite = LoadTexture(MAIN_MENU_SPRITE_PATH);

    menumgr->title_rec = (Rectangle){ 0, 0, 178, 111 };
    menumgr->title_pos = (Vector2){ GAME_WIDTH/2 - menumgr->title_rec.width/2, GAME_HEIGHT/2 - menumgr->title_rec.height };

    menumgr->choices_rec = (Rectangle){ 0, 111, 178, 26 };
    menumgr->choices_pos = (Vector2){ GAME_WIDTH/2 - menumgr->choices_rec.width/2, GAME_HEIGHT*((float)4/6) - menumgr->choices_rec.height/2 };

    menumgr->credits_rec = (Rectangle){ 0, 137, 178, 7 };
    menumgr->credits_pos = (Vector2){ GAME_WIDTH/2 - menumgr->credits_rec.width/2, GAME_HEIGHT - menumgr->credits_rec.height*1.5 };

    menumgr->cursor_rec = (Rectangle){ 0, 144, 4, 7 };
    menumgr->cursor_pos = (Vector2){ 221, 179 };

    menumgr->textcolor = (Color)WHITE;
}

void DrawTitle(mainmenu_t *menumgr) {
    DrawTextureRec(menumgr->sprite, menumgr->title_rec, menumgr->title_pos, menumgr->textcolor);
}

void DrawChoices(mainmenu_t *menumgr) {
    DrawTextureRec(menumgr->sprite, menumgr->choices_rec, menumgr->choices_pos, menumgr->textcolor);
}

void DrawCursor(mainmenu_t *menumgr) {
    DrawTextureRec(menumgr->sprite, menumgr->cursor_rec, menumgr->cursor_pos, (!menumgr->pressed_start ? WHITE : BLANK));
}

void DrawCredits(mainmenu_t *menumgr) {
    DrawTextureRec(menumgr->sprite, menumgr->credits_rec, menumgr->credits_pos, menumgr->textcolor);
}

void DrawMainMenu(mainmenu_t *menumgr) {
    DrawTitle(menumgr);
    DrawChoices(menumgr);
    DrawCursor(menumgr);
    DrawCredits(menumgr);
}

void FadeAwayTitle(mainmenu_t *menumgr) {
    if (!menumgr->pressed_start) return;
    menumgr->frametime = GetFrameTime();
    menumgr->timer += menumgr->frametime;
    if (menumgr->timer >= 0.2 && menumgr->textcolor.a > 0) {
        menumgr->timer = 0;
        menumgr->textcolor.a -= 17;
    }

    if (menumgr->textcolor.a <= 0) {
        menumgr->textcolor.a = 0;
    }
}

bool IsTitleGone(mainmenu_t *menumgr) {
    return menumgr->textcolor.a <= 0 && menumgr->timer > 2;
}