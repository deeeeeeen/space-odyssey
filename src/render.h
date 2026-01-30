#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include "raymath.h"
#include "globals.h"
#include "gui.h"
#include "star.h"
#include "frame.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"

typedef struct game_s               game_t;
typedef struct gui_s                gui_t;
typedef struct stargroup_s          stargroup_t;
typedef struct frame_s              frame_t;
typedef struct player_s             player_t;
typedef struct enemygroup_s         enemygroup_t;
typedef struct projectilegroup_s    projectilegroup_t;


typedef struct cutscene_s {
    Rectangle               top_bar;
    Rectangle               bottom_bar;
    float                   timer;
    float                   framedelta;
    float                   displacement;
} cutscene_t; 

typedef struct render_s {
    gui_t                   gui;
    stargroup_t             stars;
    Texture2D               characters;
    RenderTexture2D         background;
    RenderTexture2D         target;
    Vector2                 game_size;
    Vector2                 monitor_size;
    float                   timer;
    cutscene_t              cutscene;
} render_t;

void InitRender(render_t *rendermgr);
void RenderWindow(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemygroup_t *enemymgr, projectilegroup_t *projectilemgr);

#endif