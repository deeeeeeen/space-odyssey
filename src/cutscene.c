#include "cutscene.h"

void InitCutscene(cutscene_t *cutscenemgr) {
    cutscenemgr->top_bar = (Rectangle) { SIDEBAR_WIDTH, 
                                                -BAR_HEIGHT, 
                                                GAME_WIDTH-2*SIDEBAR_WIDTH,
                                                BAR_HEIGHT };
    cutscenemgr->bottom_bar = (Rectangle) { SIDEBAR_WIDTH, 
                                                GAME_HEIGHT, 
                                                GAME_WIDTH-2*SIDEBAR_WIDTH, 
                                                BAR_HEIGHT };
    cutscenemgr->active = true;
}

bool WaitUntilCombatStarts(cutscene_t *cutscenemgr) {
    return !cutscenemgr->active;
}

void StartCutscene(cutscene_t *cutscenemgr, str8_t *string) {
    cutscenemgr->framedelta = FrameGetDelta();

    if (cutscenemgr->displacement < BAR_HEIGHT) {
        cutscenemgr->displacement += BAR_HEIGHT/2*cutscenemgr->framedelta;
        cutscenemgr->top_bar.y += BAR_HEIGHT/2*cutscenemgr->framedelta;
        cutscenemgr->bottom_bar.y -= BAR_HEIGHT/2*cutscenemgr->framedelta;
    }
    else {
        cutscenemgr->displacement = BAR_HEIGHT;
        cutscenemgr->framedelta = ZERO;
        DrawDialogue(string, SIDEBAR_WIDTH+BAR_HEIGHT/2.0+GetFont(DIALOGUE).baseSize/2.0, GAME_HEIGHT-BAR_HEIGHT/2.0-GetFont(DIALOGUE).baseSize/2.0);
        if (IsDialogueDone(string)) {
            cutscenemgr->done = true;
        }
    }
}

void EndCutscene(cutscene_t *cutscenemgr, str8_t *string) {
    cutscenemgr->framedelta = FrameGetDelta();

    if (cutscenemgr->displacement > ZERO) {
        cutscenemgr->displacement -= BAR_HEIGHT/2*cutscenemgr->framedelta;
        cutscenemgr->top_bar.y -= BAR_HEIGHT/2*cutscenemgr->framedelta;
        cutscenemgr->bottom_bar.y  += BAR_HEIGHT/2*cutscenemgr->framedelta;
        DrawDialogue(string, SIDEBAR_WIDTH+BAR_HEIGHT/2.0+GetFont(DIALOGUE).baseSize/2.0, GAME_HEIGHT-BAR_HEIGHT/2.0-GetFont(DIALOGUE).baseSize/2.0 + (BAR_HEIGHT-cutscenemgr->displacement));
    }
    else {
        cutscenemgr->displacement = ZERO;
        cutscenemgr->framedelta = ZERO;
        cutscenemgr->active = false;
    }
}