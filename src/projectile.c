#include "projectile.h"

// returns the index of a 'dead' projectile, if none exist increment the 'projectile_count' by 1
int ReturnEmptyProjectileIdx(projectilegroup_t *projectilemgr) {
    for (int proj_idx = 0; proj_idx < projectilemgr->projectile_count; proj_idx++) {
        if (!projectilemgr->projectiles[proj_idx].alive) {
            return proj_idx;
        }
    }
    return projectilemgr->projectile_count;
}

Color ProjColorType(projectile_t *projectile) {
    return (projectile->friendly == true) ? NES_GREEN : NES_RED;
}

void UpdateProjectiles(projectilegroup_t *projectilemgr) {
    projectilemgr->framedelta = FrameGetDelta();

    for (int proj_idx = 0; proj_idx < projectilemgr->projectile_count; proj_idx++) {
        if (projectilemgr->projectiles[proj_idx].alive) { // maybe not necessary to check, but just because :)
            projectilemgr->projectiles[proj_idx].pos.x += projectilemgr->projectiles[proj_idx].move.x*projectilemgr->framedelta*60;
            projectilemgr->projectiles[proj_idx].pos.y += projectilemgr->projectiles[proj_idx].move.y*projectilemgr->framedelta*60;

            if ((projectilemgr->projectiles[proj_idx].pos.x > GAME_WIDTH || projectilemgr->projectiles[proj_idx].pos.x < 0) || (projectilemgr->projectiles[proj_idx].pos.y > GAME_HEIGHT || projectilemgr->projectiles[proj_idx].pos.y < 0)) {
                projectilemgr->projectiles[proj_idx].alive = false;
            }
        }
    }
}