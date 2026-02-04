#ifndef STAR_H
#define STAR_H
#include "raylib.h"
#include "globals.h"

#define MAX_STARS                   50
#define MAX_I8                      255
#define MAX_STARTYPE                3
#define SPACE_COLOR       (Color) { 5, 0, 19, 255 }

enum startype_e {
    DOT,
    DIAMOND,
    CROSS
};

typedef struct star_s {
    Vector2                         atls[THREEBYTHREE];
    Color                           clr[THREEBYTHREE];
} star_t;

typedef struct stargroup_s {
    star_t                          group[MAX_STARS];
    int                             count;
    RenderTexture2D                 backdrop;
} stargroup_t;

void InitStars(stargroup_t *starmgr);
void DrawStars(stargroup_t *starmgr);

#endif