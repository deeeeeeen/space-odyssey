#include "render.h"

void DrawPlayer(render_t *rendermgr, player_t *playermgr) {
    DrawTextureRec(rendermgr->characters, playermgr->sprite_rec, playermgr->pos, WHITE);
}

void DrawEnemies(render_t *rendermgr, enemygroup_t *enemymgr) {
    for (int enemy_idx = 0; enemy_idx < enemymgr->enemy_count; enemy_idx++) {
        if (enemymgr->enemies[enemy_idx].alive) {
            DrawTextureRec(rendermgr->characters, enemymgr->enemies[enemy_idx].sprite_rec, enemymgr->enemies[enemy_idx].pos, WHITE);
        }
    }
}

void DrawProjectiles(projectilegroup_t *projectilemgr) {
    for (int proj_idx = 0; proj_idx < projectilemgr->projectile_count; proj_idx++) {
        projectile_t proj = projectilemgr->projectiles[proj_idx];
        if (projectilemgr->projectiles[proj_idx].alive) {
            switch (projectilemgr->projectiles[proj_idx].type) {
                case SINGLE:
                    DrawLine(proj.pos.x, proj.pos.y-1, proj.pos.x+1, proj.pos.y+1, ProjColorType(&proj));
                    break;
                case DOUBLE:
                    DrawLine(proj.pos.x, proj.pos.y-1, proj.pos.x+1, proj.pos.y+1, ProjColorType(&proj));
                    break;
                case TRIPLE:
                    DrawLine(proj.pos.x, proj.pos.y-1, proj.pos.x+1, proj.pos.y+1, ProjColorType(&proj));
                    break;
            }
        }
    }
}

void DrawSideBar(gui_t *guimgr) {
    UpdateSidebar(guimgr);

    DrawTextureRec(guimgr->sidebars.sprite, guimgr->sidebars.base, guimgr->sidebars.base_pos_left, WHITE);
    DrawTextureRec(guimgr->sidebars.sprite, guimgr->sidebars.base, guimgr->sidebars.base_pos_right, WHITE);
    DrawTextureRec(guimgr->sidebars.sprite, guimgr->sidebars.frame, guimgr->sidebars.frame_pos_left, WHITE);
    DrawTextureRec(guimgr->sidebars.sprite, guimgr->sidebars.frame, guimgr->sidebars.frame_pos_right, WHITE);
}

void InitRender(render_t *rendermgr) {
    rendermgr->game_size = (Vector2) { GAME_WIDTH, GAME_HEIGHT };
    rendermgr->target = LoadRenderTexture(rendermgr->game_size.x, rendermgr->game_size.y);

    SetTextureFilter(rendermgr->target.texture, TEXTURE_FILTER_POINT);

    rendermgr->monitor_size = (Vector2) { GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()) };
    rendermgr->characters = LoadTexture("res/characters.png");

    rendermgr->cutscene.top_bar = (Rectangle) { 69.f, 
                                                -48.f, 
                                                rendermgr->game_size.x-69*2,
                                                48.f };
    rendermgr->cutscene.bottom_bar = (Rectangle) { 69.f, 
                                                rendermgr->game_size.y, 
                                                rendermgr->game_size.x-69*2, 
                                                48.f };

                                                
    InitStars(&rendermgr->stars);
    DrawStars(&rendermgr->stars);
    InitSidebar(&rendermgr->gui);

    TraceLog(LOG_INFO, "RENDER: Initialised!");
}

void DrawCutscene(render_t *rendermgr, player_t *playermgr, enemygroup_t *enemymgr) {
    if (!enemymgr->clear) return;
    playermgr->in_cutscene.active = true;
    rendermgr->cutscene.timer += GetFrameTime();

    if (!playermgr->in_cutscene.done) {
        if (rendermgr->cutscene.timer >= 5) {
            rendermgr->cutscene.framedelta = GetFrameTime();
            rendermgr->cutscene.timer = 5;
            if (rendermgr->cutscene.displacement < 48) {
                rendermgr->cutscene.displacement += 30*rendermgr->cutscene.framedelta;
                rendermgr->cutscene.top_bar.y += 30*rendermgr->cutscene.framedelta;
                rendermgr->cutscene.bottom_bar.y -= 30*rendermgr->cutscene.framedelta;
            }
        }
    }
    if (playermgr->in_cutscene.done) {
        rendermgr->cutscene.timer = 5;
        if (rendermgr->cutscene.displacement > 0) {
            rendermgr->cutscene.displacement -= 30*rendermgr->cutscene.framedelta;
            rendermgr->cutscene.top_bar.y -= 30*rendermgr->cutscene.framedelta;
            rendermgr->cutscene.bottom_bar.y  += 30*rendermgr->cutscene.framedelta;
        }
        else {
            enemymgr->clear = false;
            playermgr->in_cutscene.active = false;
        }
    }
    DrawRectangleRec(rendermgr->cutscene.top_bar, BLACK);
    DrawRectangleRec(rendermgr->cutscene.bottom_bar, BLACK);
}

void RenderWindow(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemygroup_t *enemymgr, projectilegroup_t *projectilemgr) {
    BeginTextureMode(rendermgr->target);
        ClearBackground(BLACK);
        BeginMode2D(framemgr->camera);
            DrawTexture(rendermgr->stars.backdrop.texture, 0, 0, WHITE);
            DrawPlayer(rendermgr, playermgr);
            DrawEnemies(rendermgr, enemymgr);
            DrawProjectiles(projectilemgr);
            DrawSideBar(&rendermgr->gui);
            DrawCutscene(rendermgr, playermgr, enemymgr);
        EndMode2D();
    EndTextureMode();

    BeginDrawing();
        DrawTexturePro(rendermgr->target.texture, 
            (Rectangle){ ZERO, ZERO, rendermgr->game_size.x, -rendermgr->game_size.y }, 
            (Rectangle){ ZERO, ZERO, rendermgr->monitor_size.x, rendermgr->monitor_size.y },
            (Vector2) {ZERO, ZERO}, 
            ZERO, 
            WHITE);
    EndDrawing();
}