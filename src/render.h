#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include "raymath.h"
#include "frame.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"

#define GAME_WIDTH         512
#define GAME_HEIGHT        288
#define MAX_STARS          50
#define GRID_3X3           9

typedef struct game_s           game_t;
typedef struct frame_s          frame_t;
typedef struct player_s         player_t;
typedef struct enemies_s        enemies_t;
typedef struct projectiles_s    projectiles_t;

typedef struct star_s {
    Vector2     atls[GRID_3X3];
    Color       clr[GRID_3X3];
} star_t;

typedef struct sidebar_s {
    Rectangle               base;
    Rectangle               frame;
    Rectangle               top_frame;
} sidebar_t;

typedef struct render_s {
    float                   delta;
    sidebar_t               gui_rec;
    Texture2D               gui_sprite;
    Texture2D               characters;
    RenderTexture2D         background;
    RenderTexture2D         target;
    Vector2                 game_size;
    Vector2                 monitor_size;
    star_t                  stars[MAX_STARS];
    int                     starcount;
} render_t;

void InitRender(render_t *rendermgr);
void RenderWindow(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemies_t *enemymgr, projectiles_t *projectilemgr);
void ProjectileCollMgr(render_t *rendermgr, projectiles_t *projectilemgr, enemies_t *enemymgr, player_t *playermgr);

#endif