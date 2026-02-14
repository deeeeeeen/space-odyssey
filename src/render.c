#include "render.h"

str8_t introstr = STR8_LITR("[???]:    Hello, Nemo. I hope you woke up and have come to your senses. The effects of\n             cryogenic hibernation will wear off shortly. \n[Nemo]: Yaaaaaawn. Somewhat. The cryo sleep did a number on me. I feel miserable. \n             Yawn... what's with the sudden wake up command? \n[???]:    Forgive me, but I am in need of your assistance. We are approaching a group of\n             aliens!");

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
    DrawTextureRec(guimgr->spritemap, guimgr->sidebars.base, (Vector2) { (int)guimgr->sidebars.base_pos_left.x, (int)guimgr->sidebars.base_pos_left.y }, WHITE);
    DrawTextureRec(guimgr->spritemap, guimgr->sidebars.base, (Vector2) { (int)guimgr->sidebars.base_pos_right.x, (int)guimgr->sidebars.base_pos_right.y }, WHITE);
    DrawTextureRec(guimgr->spritemap, guimgr->sidebars.frame, guimgr->sidebars.frame_pos_left, WHITE);
    DrawTextureRec(guimgr->spritemap, guimgr->sidebars.frame, guimgr->sidebars.frame_pos_right, WHITE);
}

void InitRender(render_t *rendermgr) {
    rendermgr->game_size = (Vector2) { GAME_WIDTH, GAME_HEIGHT };
    rendermgr->target = LoadRenderTexture(rendermgr->game_size.x, rendermgr->game_size.y);

    SetTextureFilter(rendermgr->target.texture, TEXTURE_FILTER_POINT);

    rendermgr->monitor_size = (Vector2) { GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()) };
    rendermgr->characters = LoadTexture("res/graphic/characters.png");
                                                
    InitStars(&rendermgr->stars);
    DrawStars(&rendermgr->stars);
    InitGui(&rendermgr->gui);
    InitCutscene(&rendermgr->cutscene);
    InitHud(&rendermgr->hud);

    InitMainMenu(&rendermgr->main_menu);

    TraceLog(LOG_INFO, "RENDER: Initialised!");
}

void DrawCutscene(cutscene_t *cutscenemgr, player_t *playermgr, str8_t *string) {
    if (cutscenemgr->active) {
        playermgr->in_cutscene.active = cutscenemgr->active;
    }
    if (!cutscenemgr->active) {
        playermgr->in_cutscene.active = cutscenemgr->active;
        return;
    }
    playermgr->in_cutscene.done = cutscenemgr->done;
    
    DrawRectangleRec(cutscenemgr->top_bar, BLACK);
    DrawRectangleRec(cutscenemgr->bottom_bar, BLACK);
    
    if (!cutscenemgr->done) {
        StartCutscene(cutscenemgr, string);
    }
    if (cutscenemgr->done) {
        EndCutscene(cutscenemgr, string);
    }
}

void DrawHud(hud_t *hudmgr, player_t *playermgr) {
    // hp section
    DrawRectangle(hudmgr->hp_pos.x, hudmgr->hp_pos.y, hudmgr->hp_box_size.x, playermgr->health * hudmgr->hp_box_size.y, BLACK);
    for (int hcount = 0; hcount < playermgr->health; hcount++) {
        DrawTextureRec(hudmgr->sprite, hudmgr->hp_rec, (Vector2) { hudmgr->hp_pos.x, hcount * hudmgr->hp_box_size.y + (hudmgr->hp_pos.y+3)}, WHITE);
    }
    // ----------
    // playtime section
    DrawRectangleV(hudmgr->time_pos, hudmgr->time_box_size, BLACK);
    if (hudmgr->playtime_s > 3600*9) {
        DrawTextureRec(hudmgr->sprite, (Rectangle) { 72, 0, 8, 7 }, (Vector2) { 450+128, 7 }, WHITE);
    }
    else {
        DrawTextureRec(hudmgr->sprite, (Rectangle) { ((hudmgr->playtime_s/3600)%9), 0, 8, 7 }, (Vector2) { 450+128, 7 }, WHITE);
    }
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 72, 7, 8, 7 }, (Vector2) { 458+128, 7 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((hudmgr->playtime_s/600)%6), 0, 8, 7 }, (Vector2) { 466+128, 7 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*((hudmgr->playtime_s/60)%10), 0, 8, 7 }, (Vector2) { 474+128, 7 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 72, 7, 8, 7 }, (Vector2) { 482+128, 7 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((hudmgr->playtime_s/10)%6), 0, 8, 7 }, (Vector2) { 490+128, 7 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(hudmgr->playtime_s%10), 0, 8, 7 }, (Vector2) { 498+128, 7 }, WHITE);
    // ----------------
    // level section
    DrawRectangleV(hudmgr->lvl_pos, hudmgr->lvl_box_size, BLACK);
    DrawTextureRec(hudmgr->sprite, hudmgr->lvl_rec, (Vector2) {hudmgr->lvl_pos.x, hudmgr->lvl_pos.y+3}, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 0, 0, 8, 7 }, (Vector2) { 482+128, 17 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 0, 0, 8, 7 }, (Vector2) { 490+128, 17 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8, 0, 8, 7 }, (Vector2) { 498+128, 17 }, WHITE);
    // ----------

    // score section
    DrawRectangleV(hudmgr->score_pos, hudmgr->score_box_size, BLACK);
    DrawTextureRec(hudmgr->sprite, hudmgr->score_rec, (Vector2) {hudmgr->score_pos.x, hudmgr->score_pos.y+3}, WHITE);
    if (playermgr->score > 9999999) {
        DrawTextureRec(hudmgr->sprite, (Rectangle) { 72, 0, 8, 7 }, (Vector2) { 450+128, 43 }, WHITE);
    }
    else {
        DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((playermgr->score/1000000)%10), 0, 8, 7 }, (Vector2) { 450+128, 43 }, WHITE);
    }
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((playermgr->score/100000)%10), 0, 8, 7 }, (Vector2) { 458+128, 43 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((playermgr->score/10000)%10), 0, 8, 7 }, (Vector2) { 466+128, 43 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((playermgr->score/1000)%10), 0, 8, 7 }, (Vector2) { 474+128, 43 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((playermgr->score/100)%10), 0, 8, 7 }, (Vector2) { 482+128, 43 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { 8*(int)((playermgr->score/10)%10), 0, 8, 7 }, (Vector2) { 490+128, 43 }, WHITE);
    DrawTextureRec(hudmgr->sprite, (Rectangle) { (playermgr->score%10), 0, 8, 7 }, (Vector2) { 498+128, 43 }, WHITE);
    // ----------------
}

void DrawGui(gui_t *guimgr) {
    DrawTextureRec(guimgr->spritemap, guimgr->pause_menu.window_rec, guimgr->pause_menu.window_pos, WHITE);
    DrawTextureRec(guimgr->spritemap, guimgr->pause_menu.cursor_rec, guimgr->pause_menu.cursor_pos, WHITE);
}

void RenderUpscaledGame(render_t *rendermgr) {
    int windowy = ZERO;
    float windowwidth = GetWindowResolution().x * (9.0/16.0);
    if (windowwidth != GetWindowResolution().y) { // the monitor is not 16:9 aspect ratio!!
        windowy = (int)GetWindowResolution().x / 16 / 2;
    }
    BeginDrawing();
        DrawTexturePro(rendermgr->target.texture, 
            (Rectangle){ ZERO, ZERO, (int)rendermgr->game_size.x, (int)-rendermgr->game_size.y }, 
            (Rectangle){ ZERO, windowy, (int)GetWindowResolution().x, (int)GetWindowResolution().y - 2*windowy},
            (Vector2) {ZERO, ZERO}, 
            ZERO, 
            WHITE);
    EndDrawing();
}

void RenderPauseMenu(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemygroup_t *enemymgr, projectilegroup_t *projectilemgr) {
    if (!rendermgr->pause.drawn) {
        rendermgr->pause.drawn = true;
        rendermgr->pause.frame = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
        BeginTextureMode(rendermgr->pause.frame);
            BeginMode2D(framemgr->camera);
                DrawTexture(rendermgr->stars.backdrop.texture, ZERO, ZERO, WHITE);
                DrawPlayer(rendermgr, playermgr);
                DrawEnemies(rendermgr, enemymgr);
                DrawProjectiles(projectilemgr);
                DrawSideBar(&rendermgr->gui);
                DrawHud(&rendermgr->hud, playermgr);
                DrawCutscene(&rendermgr->cutscene, playermgr, &introstr);
            EndMode2D();
        EndTextureMode();
    }
    else { 
        BeginTextureMode(rendermgr->target);
            BeginMode2D(framemgr->camera);
            DrawTexturePro(rendermgr->pause.frame.texture, 
            (Rectangle){ ZERO, ZERO, (int)rendermgr->game_size.x, (int)-rendermgr->game_size.y }, 
            (Rectangle){ ZERO, ZERO, (int)rendermgr->game_size.x, (int)rendermgr->game_size.y },
            (Vector2) {ZERO, ZERO}, 
            ZERO, 
            WHITE);
            DrawGui(&rendermgr->gui);
            EndMode2D();
        EndTextureMode();
    }

    RenderUpscaledGame(rendermgr);
}

void RenderTitle(render_t *rendermgr, frame_t *framemgr, player_t *playermgr) {
    // UPDATE
    UpdateSidebar(&rendermgr->gui);
    UpdateHud(&rendermgr->hud);
    // ---

    BeginTextureMode(rendermgr->target);
        ClearBackground(BLACK);
        BeginMode2D(framemgr->camera);
            DrawTexture(rendermgr->stars.backdrop.texture, ZERO, ZERO, WHITE);
            DrawMainMenu(&rendermgr->main_menu);
            DrawPlayer(rendermgr, playermgr);
            DrawSideBar(&rendermgr->gui);
            EndMode2D();
    EndTextureMode();

    RenderUpscaledGame(rendermgr);
}

void RenderWindow(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemygroup_t *enemymgr, projectilegroup_t *projectilemgr) {
    // UPDATE
    if (rendermgr->pause.drawn) {
        UnloadRenderTexture(rendermgr->pause.frame);
        rendermgr->pause.drawn = false;
    }
    UpdateSidebar(&rendermgr->gui);
    UpdateHud(&rendermgr->hud);
    // ---

    BeginTextureMode(rendermgr->target);
        ClearBackground(BLACK);
        BeginMode2D(framemgr->camera);
            DrawTexture(rendermgr->stars.backdrop.texture, ZERO, ZERO, WHITE);
            DrawPlayer(rendermgr, playermgr);
            DrawEnemies(rendermgr, enemymgr);
            DrawProjectiles(projectilemgr);
            DrawSideBar(&rendermgr->gui);
            DrawHud(&rendermgr->hud, playermgr);
            DrawCutscene(&rendermgr->cutscene, playermgr, &introstr);
        EndMode2D();
    EndTextureMode();

    RenderUpscaledGame(rendermgr);
}