#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include "raymath.h"
#include "frame.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"

#define GAME_WIDTH          512
#define GAME_HEIGHT         288
#define MAX_STARS           50
#define GRID_3X3            9

typedef struct game_s               game_t;
typedef struct frame_s              frame_t;
typedef struct player_s             player_t;
typedef struct enemygroup_s         enemygroup_t;
typedef struct projectilegroup_s    projectilegroup_t;

typedef struct star_s {
    Vector2     atls[GRID_3X3];
    Color       clr[GRID_3X3];
} star_t;

typedef struct cutscene_s {
    Rectangle               top_bar;
    Rectangle               bottom_bar;
    float                   timer;
    float                   displacement;
} cutscene_t; 

typedef struct sidebar_s {
    Texture2D               sprite;
    Rectangle               base;
    Rectangle               frame;
    float                   timer;
    float                   displacement;
} sidebar_t;

typedef struct render_s {
    sidebar_t               gui;
    Texture2D               characters;
    RenderTexture2D         background;
    RenderTexture2D         target;
    Vector2                 game_size;
    Vector2                 monitor_size;
    star_t                  stars[MAX_STARS];
    int                     starcount;
    float                   timer;
    cutscene_t              cutscene;
} render_t;

void InitRender(render_t *rendermgr);
void RenderWindow(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemygroup_t *enemymgr, projectilegroup_t *projectilemgr);

#endif