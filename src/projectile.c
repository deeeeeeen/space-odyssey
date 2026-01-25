#include "projectile.h"
#include <stdio.h>

// returns the index of a 'dead' projectile, if none exist increment the 'projectile_count' by 1
int ReturnEmptyProjectileIdx(projectiles_t *projectilemgr) {
    for (int proj_idx = 0; proj_idx < projectilemgr->projectile_count; proj_idx++) {
        if (!projectilemgr->projectiles[proj_idx].alive) {
            return proj_idx;
        }
    }
    return projectilemgr->projectile_count;
}

void UpdateProjectiles(projectiles_t *projectilemgr) {
    int count = 0;
    for (int proj_idx = 0; proj_idx < projectilemgr->projectile_count; proj_idx++) {
        if (projectilemgr->projectiles[proj_idx].alive) { // maybe not necessary to check, but just because :)
            count++;
            projectilemgr->projectiles[proj_idx].pos.x += projectilemgr->projectiles[proj_idx].move.x;
            projectilemgr->projectiles[proj_idx].pos.y += projectilemgr->projectiles[proj_idx].move.y;

            if ((projectilemgr->projectiles[proj_idx].pos.x > GAME_WIDTH || projectilemgr->projectiles[proj_idx].pos.x < 0) || (projectilemgr->projectiles[proj_idx].pos.y > GAME_HEIGHT || projectilemgr->projectiles[proj_idx].pos.y < 0)) {
                projectilemgr->projectiles[proj_idx].alive = false;
            }
        }
    }

    TraceLog(LOG_INFO, TextFormat("Numbers of projectiles still alive: %d", projectilemgr->projectile_count));
}