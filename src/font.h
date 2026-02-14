#ifndef FONT_H
#define FONT_H
#include "raylib.h"
#include "font.h"

typedef enum FontId_e {
    DIALOGUE,
    FONT_COUNT
} FontId;

void InitFont();
Font GetFont(FontId id);

#endif