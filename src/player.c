#include "player.h"

void GeneratePlayerProjectiles(player_t *playermgr, projectilegroup_t *projectilemgr) {
    if (playermgr->in_cutscene.active) return;
    if (IsKeyPressed(GetControl(C_SHOOT))) {
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
    playermgr->pos          = (Vector2) { GAME_WIDTH/2, GAME_HEIGHT };
    playermgr->speed        = GAME_WIDTH/(2*2*60); // move half of the screen in two seconds running the game at 60 fps
    playermgr->health = 3;

    TraceLog(LOG_INFO, "PLAYER: Initialised!");
}

void InitPlayerInCutscene(player_t *playermgr) {
    if (!playermgr->in_cutscene.active) return;
    playermgr->in_cutscene.framedelta = FrameGetDelta();

    if (!playermgr->in_cutscene.done) {
        if (playermgr->pos.y != GAME_HEIGHT-PLAYER_HEIGHT-60-1) {
            playermgr->pos.y -= 30*playermgr->in_cutscene.framedelta;
            if (playermgr->pos.y <= GAME_HEIGHT-PLAYER_HEIGHT-60-1) {
                playermgr->pos.y = GAME_HEIGHT-PLAYER_HEIGHT-60-1;
            }
        }
    }
    else if (playermgr->in_cutscene.done) {
        if (playermgr->pos.y != GAME_HEIGHT-PLAYER_HEIGHT-1) {
            playermgr->pos.y += 30*playermgr->in_cutscene.framedelta;
            if (playermgr->pos.y >= GAME_HEIGHT-PLAYER_HEIGHT-1) {
                playermgr->pos.y = GAME_HEIGHT-PLAYER_HEIGHT-1;
                playermgr->in_cutscene.active = false;
            }
        }
    }
}

void UpdatePosition(player_t *playermgr) {
    if (IsKeyDown(GetControl(C_MOVE_LEFT))) {
        playermgr->pos.x -= playermgr->speed*playermgr->deltaframe*60;
        if (playermgr->pos.x < 69) {
            playermgr->pos.x = 69;
        }
    }
    if (IsKeyDown(GetControl(C_MOVE_RIGHT))) {
        playermgr->pos.x += playermgr->speed*playermgr->deltaframe*60;
        if (playermgr->pos.x > GAME_WIDTH-69-PLAYER_WIDTH) {
            playermgr->pos.x = GAME_WIDTH-69-PLAYER_WIDTH;
        }
    }
}

void UpdatePlayerInput(player_t *playermgr, projectilegroup_t *projectilemgr) {
    playermgr->deltaframe = FrameGetDelta();
    InitPlayerInCutscene(playermgr);
    UpdatePosition(playermgr);
    GeneratePlayerProjectiles(playermgr, projectilemgr);
}

void UpdatePlayer(player_t *playermgr, projectilegroup_t *projectilemgr) {
    UpdatePlayerInput(playermgr, projectilemgr);
}