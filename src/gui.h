#ifndef GUI_H
#define GUI_H
#include "raylib.h"
#include "globals.h"

typedef struct sidebar_s {
    Texture2D               sprite;
    Rectangle               base;
    Rectangle               frame;
    Vector2                 base_pos_left;
    Vector2                 base_pos_right;
    Vector2                 frame_pos_left;
    Vector2                 frame_pos_right;
    float                   framedelta;
    float                   displacement;
} sidebar_t;

typedef struct gui_s
{
    sidebar_t               sidebars;
} gui_t;

void InitSidebar(gui_t *guimgr);
void UpdateSidebar(gui_t *guimgr);
#endif