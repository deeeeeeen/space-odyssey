#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "frame.h"
#include "projectile.h"

#define MAX_ENEMIES         100
#define ENEMY_WIDTH         17
#define ENEMY_HEIGHT        16
#define GAME_WIDTH          640
#define GAME_HEIGHT         360

enum level1_e {
    LEFT,
    RIGHT,
    DOWN
};

enum enemy_e {
    NORMAL,
    BOSS
};

typedef struct projectilegroup_s projectilegroup_t;

typedef struct level1_s {
    int         dirs[6];
    int         dir_idx;
    float       proj_delta;
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

typedef struct enemygroup_s {
    enemy_t     enemies[MAX_ENEMIES];
    int         enemy_count;
    float       alive_count;
    float       timer;
    bool        clear;
    bool        started;
    level1_t    level1;    
} enemygroup_t;

void InitEnemy(enemygroup_t *enemymgr);
void UpdateEnemy(enemygroup_t *enemymgr, projectilegroup_t *projectilemgr);
bool HasLevelStarted(enemygroup_t *enemymgr);

#endif