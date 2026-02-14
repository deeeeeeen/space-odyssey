#include "font.h"

static Font fonts[FONT_COUNT];

void InitFont() {
    fonts[DIALOGUE] = LoadFontEx("res/font/PIXEARG_.ttf", 11, ((void*)0), 0);
    SetTextureFilter(fonts[DIALOGUE].texture, TEXTURE_FILTER_POINT);
}

Font GetFont(FontId id) {
    return fonts[id];
}