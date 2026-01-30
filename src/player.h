#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "projectile.h"

#define PLAYER_WIDTH        17
#define PLAYER_HEIGHT       16
#define GAME_WIDTH          512
#define GAME_HEIGHT         288

typedef struct projectilegroup_s projectilegroup_t;

typedef struct cutscene {
    bool        active;
    float       timer;
    float       framedelta;
    bool        done;
} cutscene;

typedef struct player_s {
    Rectangle   sprite_rec;
    Vector2     pos;
    float       speed;
    int         health;
    int         projectile_type;
    float       deltaframe;
    cutscene    in_cutscene;
} player_t;

void InitPlayer(player_t *playermgr);
void UpdatePlayer(player_t *playermgr, projectilegroup_t *projectilemgr);

#endif