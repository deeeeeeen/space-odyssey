#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include "raymath.h"
#include "globals.h"
#include "cutscene.h"
#include "main-menu.h"
#include "dialogue.h"
#include "gui.h"
#include "star.h"
#include "frame.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"

typedef struct game_s               game_t;
typedef struct cutscene_s           cutscene_t;
typedef struct mainmenu_s               mainmenu_t;
typedef struct gui_s                gui_t;
typedef struct stargroup_s          stargroup_t;
typedef struct frame_s              frame_t;
typedef struct player_s             player_t;
typedef struct enemygroup_s         enemygroup_t;
typedef struct projectilegroup_s    projectilegroup_t;

typedef struct render_s {
    mainmenu_t                  main_menu;
    gui_t                   gui;
    stargroup_t             stars;
    cutscene_t              cutscene;
    Texture2D               characters;
    RenderTexture2D         background;
    RenderTexture2D         target;
    Vector2                 game_size;
    Vector2                 monitor_size;
    float                   timer;
} render_t;

void InitRender(render_t *rendermgr);
void RenderTitle(render_t *rendermgr, frame_t *framemgr);
void RenderWindow(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemygroup_t *enemymgr, projectilegroup_t *projectilemgr);

#endif