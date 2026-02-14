#ifndef GUI_H
#define GUI_H
#include "raylib.h"
#include "frame.h"
#include "globals.h"

#define PM_CURSOR_RESUME_POS 137+36
#define PM_CURSOR_EXIT_POS  PM_CURSOR_RESUME_POS+10
#define PM_DIST_BETWEEN_CHOICES 10

typedef struct sidebar_s {
    Rectangle               base;
    Rectangle               frame;
    Vector2                 base_pos_left;
    Vector2                 base_pos_right;
    Vector2                 frame_pos_left;
    Vector2                 frame_pos_right;
    float                   framedelta;
    float                   displacement;
} sidebar_t;

typedef struct pause_menu_s {
    Rectangle               window_rec;
    Vector2                 window_pos;
    Rectangle               cursor_rec;
    Vector2                 cursor_pos;
    bool                    exiting;
    float                   frametime;
} pause_menu_t;

typedef struct gui_s
{
    Texture2D               spritemap;
    sidebar_t               sidebars;
    pause_menu_t            pause_menu;
} gui_t;

void InitGui(gui_t *guimgr);
void UpdateSidebar(gui_t *guimgr);
#endif