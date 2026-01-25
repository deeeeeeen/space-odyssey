#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "projectile.h"

#define MAX_ENEMIES         100
#define ENEMY_WIDTH         17
#define ENEMY_HEIGHT        16
#define GAME_WIDTH          512
#define GAME_HEIGHT         288

enum level1_e {
    LEFT,
    RIGHT,
    DOWN
};

enum enemy_e {
    NORMAL,
    BOSS
};

typedef struct projectiles_s projectiles_t;

typedef struct level1_s {
    int         dirs[6];
    int         dir_idx;
    float       proj_delta;
    float       alive_percentage;
} level1_t;

typedef struct enemy_s {
    Rectangle   sprite_rec;
    Vector2     pos;
    float       speed;
    int         health;
    int         level;
    int         category;
    bool        alive;
} enemy_t;

typedef struct enemies_s {
    enemy_t     enemies[MAX_ENEMIES];
    int         enemy_count;
    float       timer;
    level1_t    level1;    
} enemies_t;

void InitEnemy(enemies_t *enemymgr);
void UpdateEnemy(enemies_t *enemymgr, projectiles_t *projectilemgr);

#endif