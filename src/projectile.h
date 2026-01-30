#ifndef PORJECTILE_H
#define PORJECTILE_H

#include "raylib.h"
#include "globals.h"

#define MAX_PROJECTILES     100

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
    float           framedelta;
} projectilegroup_t;

int ReturnEmptyProjectileIdx(projectilegroup_t *projectilemgr);
Color ProjColorType(projectile_t *projectile);
void UpdateProjectiles(projectilegroup_t *projectilemgr);

#endif