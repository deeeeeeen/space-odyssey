#include "physics.h"

void ProjectileCollMgr(projectilegroup_t *projectilemgr, enemygroup_t *enemymgr, player_t *playermgr) {
    int proj_size = projectilemgr->projectile_count;
    int enemy_size = enemymgr->enemy_count;

    for (int proj_idx = 0; proj_idx < proj_size; proj_idx++) {
        for (int enemy_idx = 0; enemy_idx < enemy_size; enemy_idx++) {
            bool alive_enemy = enemymgr->enemies[enemy_idx].alive;
            bool friendly_proj = projectilemgr->projectiles[proj_idx].friendly;

            if (friendly_proj && alive_enemy) {
                Vector2 proj_pos = projectilemgr->projectiles[proj_idx].pos;
                Vector2 enemy_coll_center = {enemymgr->enemies[enemy_idx].pos.x + 9, enemymgr->enemies[enemy_idx].pos.y + 9};
                float radius = 7.f;

                if (CheckCollisionPointCircle(proj_pos, enemy_coll_center, radius)) {
                    projectilemgr->projectiles[proj_idx].alive = false;
                    projectilemgr->projectiles[proj_idx].pos = (Vector2) { 0.f, 0.f }; // i NEED to move the projectile otherwise the game will implode
                    enemymgr->enemies[enemy_idx].health--;
                    if (enemymgr->enemies[enemy_idx].health <= 0) {
                        enemymgr->enemies[enemy_idx].alive = false;
                        enemymgr->alive_count--;
                        playermgr->score += 100;
                    }
                }
            }
            if (!friendly_proj) {
                Vector2 proj_pos = projectilemgr->projectiles[proj_idx].pos;
                Vector2 player_coll_center = {playermgr->pos.x + 9, playermgr->pos.y + 9};
                float radius = 8.f;

                if (CheckCollisionPointCircle(proj_pos, player_coll_center, radius)) {
                    projectilemgr->projectiles[proj_idx].alive = false;
                    projectilemgr->projectiles[proj_idx].pos = (Vector2) { 0.f, 0.f };
                    playermgr->health--;
                }
            }
        }
    }
}