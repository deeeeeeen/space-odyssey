#include "render.h"

void GenerateStars(render_t *rendermgr) {
    int starType = GetRandomValue(0,3);
    int starX    = GetRandomValue(0, rendermgr->game_size.x);
    int starY    = GetRandomValue(0, rendermgr->game_size.y);
    
    star_t star = {
        .atls[0] = (Vector2) {starX, starY},
        .atls[1] = (Vector2) {starX+1, starY},
        .atls[2] = (Vector2) {starX+2, starY},
        .atls[3] = (Vector2) {starX, starY+1},
        .atls[4] = (Vector2) {starX+1, starY+1},
        .atls[5] = (Vector2) {starX+2, starY+1},
        .atls[6] = (Vector2) {starX, starY+2},
        .atls[7] = (Vector2) {starX+1, starY+2},
        .atls[8] = (Vector2) {starX+2, starY+2}
    };
    
    switch (starType) {
        case 0: {
            star.clr[4] = WHITE;
            break;
        }
        case 1: {
            star.clr[1] = WHITE;
            star.clr[3] = WHITE;
            star.clr[4] = WHITE;
            star.clr[5] = WHITE;
            star.clr[7] = WHITE;
            break;
        }
        case 2: {
            star.clr[0] = WHITE;
            star.clr[2] = WHITE;
            star.clr[4] = WHITE;
            star.clr[6] = WHITE;
            star.clr[8] = WHITE;
            break;
        }
        default: {
            break;
        }
    }

    for (int i = 0; i < MAX_STARS; i++) {
        for (int j = 0; j < 9; j++) {
            star.clr[j].a = GetRandomValue(0, 255);
        }
    }
    
    rendermgr->stars[rendermgr->starcount] = star;
    rendermgr->starcount++;
}

void InitStars(render_t *rendermgr) {
    rendermgr->starcount = 0;
    for (int i = 0; i < MAX_STARS; i++) {
        GenerateStars(rendermgr);
    }
}

void DrawStars(render_t *rendermgr) {
    rendermgr->background = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    BeginTextureMode(rendermgr->background);
        ClearBackground(BLACK);
        for (int i = 0; i < MAX_STARS; i++) {
            for (int j = 0; j < GRID_3X3; j++) {
                DrawPixelV(rendermgr->stars[i].atls[j], rendermgr->stars[i].clr[j]);
            }
        }
    EndDrawing();
}

void DrawPlayer(render_t *rendermgr, player_t *playermgr) {
    DrawTextureRec(rendermgr->characters, playermgr->sprite_rec, playermgr->pos, WHITE);
}

void DrawEnemies(render_t *rendermgr, enemies_t *enemymgr) {
    for (int enemy_idx = 0; enemy_idx < enemymgr->enemy_count; enemy_idx++) {
        if (enemymgr->enemies[enemy_idx].alive) {
            DrawTextureRec(rendermgr->characters, enemymgr->enemies[enemy_idx].sprite_rec, enemymgr->enemies[enemy_idx].pos, WHITE);
        }
    }
}

void DrawProjectiles(render_t *rendermgr, projectiles_t *projectilemgr) {
    for (int proj_idx = 0; proj_idx < projectilemgr->projectile_count; proj_idx++) {
        projectile_t proj = projectilemgr->projectiles[proj_idx];
        if (projectilemgr->projectiles[proj_idx].alive) {
            switch (projectilemgr->projectiles[proj_idx].type) {
                case SINGLE:
                    DrawLine(proj.pos.x, proj.pos.y-1, proj.pos.x+1, proj.pos.y+1, WHITE);
                    break;
                case DOUBLE:
                    DrawLine(proj.pos.x, proj.pos.y-1, proj.pos.x+1, proj.pos.y+1, WHITE);
                    break;
                case TRIPLE:
                    DrawLine(proj.pos.x, proj.pos.y-1, proj.pos.x+1, proj.pos.y+1, WHITE);
                    break;
            }
        }
    }
}



void DrawSideBar(render_t *rendermgr) {
    rendermgr->gui.timer += GetFrameTime();

    if (rendermgr->gui.timer >= 3.2/60) {
        rendermgr->gui.timer = 0;
        rendermgr->gui.displacement++;
        if (rendermgr->gui.displacement >= 32) {
            rendermgr->gui.displacement = 0;
        }
    }

    Vector2 base_pos_left = { 0.f, -(rendermgr->gui.base.height-GAME_HEIGHT)+rendermgr->gui.displacement };
    Vector2 base_pos_right = { GAME_WIDTH-rendermgr->gui.base.width, -(rendermgr->gui.base.height-GAME_HEIGHT)+rendermgr->gui.displacement };
    Vector2 frame_pos_left = { 0.f, -(rendermgr->gui.base.height-GAME_HEIGHT) };
    Vector2 frame_pos_right = { GAME_WIDTH-rendermgr->gui.base.width, -(rendermgr->gui.base.height-GAME_HEIGHT) };

    DrawTextureRec(rendermgr->gui.sprite, rendermgr->gui.base, base_pos_left, WHITE);
    DrawTextureRec(rendermgr->gui.sprite, rendermgr->gui.base, base_pos_right, WHITE);

    DrawTextureRec(rendermgr->gui.sprite, rendermgr->gui.frame, frame_pos_left, WHITE);
    DrawTextureRec(rendermgr->gui.sprite, rendermgr->gui.frame, frame_pos_right, WHITE);
}

void ProjectileCollMgr(render_t *rendermgr, projectiles_t *projectilemgr, enemies_t *enemymgr, player_t *playermgr) {
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

void InitRender(render_t *rendermgr) {
    rendermgr->game_size = (Vector2) { GAME_WIDTH, GAME_HEIGHT };
    rendermgr->target = LoadRenderTexture(rendermgr->game_size.x, rendermgr->game_size.y);

    SetTextureFilter(rendermgr->target.texture, TEXTURE_FILTER_POINT);

    rendermgr->monitor_size = (Vector2) { GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()) };
    rendermgr->characters = LoadTexture("res/characters.png");

    // sidebars
    rendermgr->gui.sprite = LoadTexture("res/gui.png");
    rendermgr->gui.base = (Rectangle) { 69.f, 0.f, 69.f, 320.f };
    rendermgr->gui.frame = (Rectangle) { 0.f, 0.f, 69.f, 320.f };
    // ---

    InitStars(rendermgr);
    DrawStars(rendermgr);

    TraceLog(LOG_INFO, "RENDER: Initialised!");
}

void RenderWindow(render_t *rendermgr, frame_t *framemgr, player_t *playermgr, enemies_t *enemymgr, projectiles_t *projectilemgr) {
    BeginTextureMode(rendermgr->target);
        ClearBackground(BLACK);
        BeginMode2D(framemgr->camera);
            DrawTexture(rendermgr->background.texture, 0, 0, WHITE);
            DrawPlayer(rendermgr, playermgr);
            DrawEnemies(rendermgr, enemymgr);
            DrawProjectiles(rendermgr, projectilemgr);
            DrawSideBar(rendermgr);
        EndMode2D();
    EndTextureMode();

    BeginDrawing();
        DrawTexturePro(rendermgr->target.texture, 
            (Rectangle){ 0, 0, (float)rendermgr->game_size.x, -(float)rendermgr->game_size.y }, 
            (Rectangle){ 0, 0, (float)rendermgr->monitor_size.x, (float)rendermgr->monitor_size.y },
            (Vector2) {0.f, 0.f}, 
            0.0f, 
            WHITE);
    EndDrawing();
}