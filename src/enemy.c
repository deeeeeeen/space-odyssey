#include "enemy.h"

void PrepareLevel1Enemies(enemies_t *enemymgr) {
    for (int enemy_idx = 0; enemy_idx < MAX_ENEMIES; enemy_idx++) {
        enemymgr->enemies[enemy_idx].sprite_rec = (Rectangle) { ENEMY_WIDTH, 0.f, ENEMY_WIDTH, ENEMY_HEIGHT };
        enemymgr->enemies[enemy_idx].pos = (Vector2) { (GAME_WIDTH-20*ENEMY_WIDTH)/2 + ENEMY_WIDTH*(enemy_idx%20), ENEMY_HEIGHT + ((int)(enemy_idx/20))*ENEMY_HEIGHT };
        enemymgr->enemies[enemy_idx].health = 1;
        enemymgr->enemies[enemy_idx].speed = 0;
        enemymgr->enemies[enemy_idx].level = 1;
        enemymgr->enemies[enemy_idx].category = NORMAL;
        enemymgr->enemies[enemy_idx].alive = true;
        enemymgr->enemy_count++;
    }
}

void InitEnemy(enemies_t *enemymgr) {
    
    enemymgr->enemy_count = 0;
    PrepareLevel1Enemies(enemymgr);

    TraceLog(LOG_INFO, "ENEMIES: Initialised!");
}

void Level1Behaviour(enemies_t *enemymgr) {
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

    
}

void UpdatePositions(enemies_t *enemymgr) {
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
            Level1Behaviour(enemymgr);
            break;
    }
}

void UpdateEnemy(enemies_t *enemymgr) {
    enemymgr->delta = GetFrameTime();
    UpdatePositions(enemymgr);
}