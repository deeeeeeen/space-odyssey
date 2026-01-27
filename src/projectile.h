#ifndef PORJECTILE_H
#define PORJECTILE_H

#include "raylib.h"

#define MAX_PROJECTILES     100
#define GAME_WIDTH          512
#define GAME_HEIGHT         288



enum projectile_type {
    SINGLE,
    DOUBLE,
    TRIPLE
};

typedef struct projectile_s {
    int             type;
    Vector2         move;
    bool            friendly;
    bool            alive;
    Vector2         pos;
} projectile_t;

typedef struct projectilegroup_s {
    projectile_t    projectiles[MAX_PROJECTILES];
    int             projectile_count;
} projectilegroup_t;

int ReturnEmptyProjectileIdx(projectilegroup_t *projectilemgr);
void UpdateProjectiles(projectilegroup_t *projectilemgr);

#endif