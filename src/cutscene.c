#include "cutscene.h"

void InitCutscene(cutscene_t *cutscenemgr) {
    cutscenemgr->top_bar = (Rectangle) { 69.f, 
                                                -48.f, 
                                                GAME_WIDTH-69*2,
                                                48.f };
    cutscenemgr->bottom_bar = (Rectangle) { 69.f, 
                                                GAME_HEIGHT, 
                                                GAME_WIDTH-69*2, 
                                                48.f };
}

void StartCutscene(cutscene_t *cutscenemgr) {
    cutscenemgr->framedelta = GetFrameTime();

    if (cutscenemgr->displacement < 48) {
        cutscenemgr->displacement += 30*cutscenemgr->framedelta;
        cutscenemgr->top_bar.y += 30*cutscenemgr->framedelta;
        cutscenemgr->bottom_bar.y -= 30*cutscenemgr->framedelta;
    }
    else {
        cutscenemgr->displacement = 48;
        cutscenemgr->framedelta = 0;
    }
}

void EndCutscene(cutscene_t *cutscenemgr) {
    cutscenemgr->framedelta = GetFrameTime();

    if (cutscenemgr->displacement > 0) {
        cutscenemgr->displacement -= 30*cutscenemgr->framedelta;
        cutscenemgr->top_bar.y -= 30*cutscenemgr->framedelta;
        cutscenemgr->bottom_bar.y  += 30*cutscenemgr->framedelta;
    }
    else {
        cutscenemgr->displacement = 0;
        cutscenemgr->framedelta = 0;
    }
}