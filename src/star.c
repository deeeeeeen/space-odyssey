#include "star.h"

void GenerateStars(stargroup_t *starmgr) {
    int startype = GetRandomValue(ZERO, MAX_STARTYPE);
    int starX    = GetRandomValue(ZERO, GAME_WIDTH);
    int starY    = GetRandomValue(ZERO, GAME_HEIGHT);
    
    star_t star = {
        .atls[0] = (Vector2) {starX, starY},
        .atls[1] = (Vector2) {starX+1, starY},
        .atls[2] = (Vector2) {starX+2, starY},
        .atls[3] = (Vector2) {starX, starY+1},
        .atls[4] = (Vector2) {starX+1, starY+1},
        .atls[5] = (Vector2) {starX+2, starY+1},
        .atls[6] = (Vector2) {starX, starY+2},
        .atls[7] = (Vector2) {starX+1, starY+2},
        .atls[8] = (Vector2) {starX+2, starY+2}
    };
    
    switch (startype) {
        case DOT: {
            star.clr[4] = WHITE;
            break;
        }
        case DIAMOND: {
            star.clr[1] = WHITE;
            star.clr[3] = WHITE;
            star.clr[4] = WHITE;
            star.clr[5] = WHITE;
            star.clr[7] = WHITE;
            break;
        }
        case CROSS: {
            star.clr[0] = WHITE;
            star.clr[2] = WHITE;
            star.clr[4] = WHITE;
            star.clr[6] = WHITE;
            star.clr[8] = WHITE;
            break;
        }
    }

    for (int i = ZERO; i < MAX_STARS; i++) {
        for (int j = ZERO; j < THREEBYTHREE; j++) {
            star.clr[j].a = GetRandomValue(ZERO, MAX_I8);
        }
    }
    
    starmgr->group[starmgr->count] = star;
    starmgr->count++;
}

void InitStars(stargroup_t *starmgr) {
    starmgr->count = ZERO;
    for (int i = ZERO; i < MAX_STARS; i++) {
        GenerateStars(starmgr);
    }
}

void DrawStars(stargroup_t *starmgr) {
    starmgr->backdrop = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    BeginTextureMode(starmgr->backdrop);
        ClearBackground(SPACE_COLOR);
        for (int i = ZERO; i < MAX_STARS; i++) {
            for (int j = ZERO; j < THREEBYTHREE; j++) {
                DrawPixelV(starmgr->group[i].atls[j], starmgr->group[i].clr[j]);
            }
        }
    EndDrawing();
}