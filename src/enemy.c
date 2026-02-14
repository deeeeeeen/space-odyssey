#include "enemy.h"

void PrepareLevel1Enemies(enemygroup_t *enemymgr) {
    enemymgr->level1.dirs[0] = RIGHT;
    enemymgr->level1.dirs[1] = DOWN;
    enemymgr->level1.dirs[2] = LEFT;
    enemymgr->level1.dirs[3] = LEFT;
    enemymgr->level1.dirs[4] = DOWN;
    enemymgr->level1.dirs[5] = RIGHT;

    for (int enemy_idx = 0; enemy_idx < MAX_ENEMIES; enemy_idx++) {
        enemymgr->enemies[enemy_idx].sprite_rec = (Rectangle) { ENEMY_WIDTH, 0.f, ENEMY_WIDTH, ENEMY_HEIGHT };
        enemymgr->enemies[enemy_idx].pos = (Vector2) { (GAME_WIDTH-20*ENEMY_WIDTH)/2 + ENEMY_WIDTH*(enemy_idx%20), -(MAX_ENEMIES/20)*ENEMY_HEIGHT + ((int)(enemy_idx/20))*ENEMY_HEIGHT };
        enemymgr->enemies[enemy_idx].health = 1;
        enemymgr->enemies[enemy_idx].speed = 0;
        enemymgr->enemies[enemy_idx].level = 1;
        enemymgr->enemies[enemy_idx].category = NORMAL;
        enemymgr->enemies[enemy_idx].alive = true;
        enemymgr->enemy_count++;
        enemymgr->alive_count++;
    }
}

void InitEnemy(enemygroup_t *enemymgr) {
    
    enemymgr->enemy_count = 0;
    PrepareLevel1Enemies(enemymgr);

    TraceLog(LOG_INFO, "ENEMIES: Initialised!");
}

int ReturnRandomAliveEnemyIdx(enemygroup_t *enemymgr) {
    int random_idx = 0;
    while (1) {
        random_idx = GetRandomValue(0, MAX_ENEMIES-1);
        if (enemymgr->enemies[random_idx].alive) {
            break;
        }
    }

    return random_idx;
}

void GenerateEnemyProjectiles(enemygroup_t *enemymgr, projectilegroup_t *projectilemgr) {
    int new_proj_idx = ReturnEmptyProjectileIdx(projectilemgr);
    int alive_enemy_idx = ReturnRandomAliveEnemyIdx(enemymgr);

    projectile_t new_projectile = { 0 };
    new_projectile.alive = true;
    new_projectile.friendly = false;
    new_projectile.type = SINGLE;

    Vector2 enemy_pos = enemymgr->enemies[alive_enemy_idx].pos;

    switch (new_projectile.type) {
        case SINGLE:
            new_projectile.move = (Vector2) { 0.f, 1.f};
            new_projectile.pos.x = enemy_pos.x+8;
            new_projectile.pos.y = enemy_pos.y+ENEMY_HEIGHT;
            projectilemgr->projectiles[new_proj_idx] = new_projectile;
    
            if (new_proj_idx == projectilemgr->projectile_count) {
                projectilemgr->projectile_count++;
            }
        break;
    }
}

float ReturnAliveEnemies(enemygroup_t *enemymgr) {
    return enemymgr->alive_count;
}

void Level1Behaviour(enemygroup_t *enemymgr, projectilegroup_t *projectilemgr) {
   /*
    * this ai follows the usual space invader movement + some projectiles
    *
    * movement route:
    *       ->
    *        v
    * <- <- <-
    * v
    * -> -> 
    * 
    */

    enemymgr->clear = ReturnAliveEnemies(enemymgr) == 0;

    if (!enemymgr->clear) {
        enemymgr->timer += FrameGetDelta();
        enemymgr->level1.proj_delta += FrameGetDelta();

        if (enemymgr->level1.proj_delta >= .25*(1/(enemymgr->alive_count/MAX_ENEMIES))) { // very dirty way of decreasing the rate of fire the lesser enemies are alive
            enemymgr->level1.proj_delta = 0;
            GenerateEnemyProjectiles(enemymgr, projectilemgr);
        }

        if (enemymgr->timer >= 1) {
            enemymgr->timer = 0;

            switch(enemymgr->level1.dirs[enemymgr->level1.dir_idx]) {
                case LEFT:
                    for (int i = 0; i < enemymgr->enemy_count; i++) {
                        if (enemymgr->enemies[i].alive) {
                            enemymgr->enemies[i].pos.x -= ENEMY_WIDTH;
                        }
                    }
                break;
                case RIGHT:
                    for (int i = 0; i < enemymgr->enemy_count; i++) {
                        if (enemymgr->enemies[i].alive) {
                            enemymgr->enemies[i].pos.x += ENEMY_WIDTH;
                        }
                    }
                break;
                case DOWN:
                    for (int i = 0; i < enemymgr->enemy_count; i++) {
                        if (enemymgr->enemies[i].alive) {
                            enemymgr->enemies[i].pos.y += ENEMY_HEIGHT;
                        }
                    }
                break;
            }

            enemymgr->level1.dir_idx++;
            
            if (enemymgr->level1.dir_idx >= 6) {
                enemymgr->level1.dir_idx = 0;
            }
        }
    }
}

void UpdatePositions(enemygroup_t *enemymgr, projectilegroup_t *projectilemgr) {
    int level = 1;
    for (int i = 0; i < enemymgr->enemy_count; i++) {
        if (enemymgr->enemies[i].alive) {
            level = enemymgr->enemies[i].level;
            break;
        }
    }

    switch (level)
    {
        case 1:
            Level1Behaviour(enemymgr, projectilemgr);
        break;
    }
}

void UpdateEnemy(enemygroup_t *enemymgr, projectilegroup_t *projectilemgr) {
    UpdatePositions(enemymgr, projectilemgr);
}