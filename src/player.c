#include "player.h"

void GeneratePlayerProjectiles(player_t *playermgr, projectiles_t *projectilemgr) {
    if (IsKeyPressed(KEY_LEFT_CONTROL)) {
        int new_proj_idx = ReturnEmptyProjectileIdx(projectilemgr);

        projectile_t new_projectile = { 0 };
        new_projectile.alive = true;
        new_projectile.friendly = true;
        new_projectile.type = 0;

        switch (new_projectile.type) {
            case SINGLE:
                new_projectile.move = (Vector2) { 0.f, -2.f};
                new_projectile.pos.x = playermgr->pos.x+8;
                new_projectile.pos.y = playermgr->pos.y;
                projectilemgr->projectiles[new_proj_idx] = new_projectile;
        
                if (new_proj_idx == projectilemgr->projectile_count) {
                    projectilemgr->projectile_count++;
                }
                break;
            case DOUBLE:
                new_projectile.move = (Vector2) { 0.f, -3.f};
                projectile_t new_projectile2 = new_projectile;

                new_projectile.pos.x = playermgr->pos.x+6;
                new_projectile2.pos.x = playermgr->pos.x+10;
                new_projectile.pos.y = playermgr->pos.y;
                new_projectile2.pos.y = playermgr->pos.y;
        
                projectilemgr->projectiles[new_proj_idx] = new_projectile;

                if (new_proj_idx == projectilemgr->projectile_count) {
                    projectilemgr->projectile_count++;
                }

                int new_proj_idx2 = ReturnEmptyProjectileIdx(projectilemgr);

                projectilemgr->projectiles[new_proj_idx2] = new_projectile2;
                if (new_proj_idx2 == projectilemgr->projectile_count) {
                    projectilemgr->projectile_count++;
                }

                break;
            case TRIPLE:
                new_projectile.move = (Vector2) { 0.f, -2.f};
                new_projectile.pos = playermgr->pos;
                break;
        }
    }
}

void InitPlayer(player_t *playermgr) {
    playermgr->sprite_rec   = (Rectangle) { 0.f, 0.f, PLAYER_WIDTH, PLAYER_HEIGHT };
    playermgr->pos          = (Vector2) { GAME_WIDTH/2, GAME_HEIGHT-PLAYER_HEIGHT };
    playermgr->speed        = GAME_WIDTH/(2*2*60); // move half of the screen in two seconds running the game at 60 fps

    TraceLog(LOG_INFO, "PLAYER: Initialised!");
}

void UpdatePosition(player_t *playermgr) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        playermgr->pos.x -= playermgr->speed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        playermgr->pos.x += playermgr->speed;
    }
}

void UpdatePlayerInput(player_t *playermgr, projectiles_t *projectilemgr) {
    UpdatePosition(playermgr);
    GeneratePlayerProjectiles(playermgr, projectilemgr);
}

void UpdatePlayer(player_t *playermgr, projectiles_t *projectilemgr) {
    UpdatePlayerInput(playermgr, projectilemgr);
}