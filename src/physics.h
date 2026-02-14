#ifndef PHYSICS_H
#define PHYSICS_H

#include "raylib.h"
#include "audio.h"
#include "projectile.h"
#include "player.h"
#include "enemy.h"

typedef struct projectilegroup_s    projectilegroup_t;
typedef struct player_s             player_t;
typedef struct enemygroup_s         enemygroup_t;


void ProjectileCollMgr(projectilegroup_t *projectilemgr, enemygroup_t *enemymgr, player_t *playermgr);

#endif