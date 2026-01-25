#ifndef GAME_H
#define GAME_H

#include "render.h"
#include "frame.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "logger.h"
#include <time.h>
#include <string.h>

#define GAME_TITLE         "space odyssey"
#define GAME_FPS           60

typedef struct render_s         render_t;
typedef struct player_s         player_t;
typedef struct enemies_s        enemies_t;
typedef struct frame_s          frame_t;
typedef struct projectiles_s    projectiles_t;

typedef struct game_s {
    render_t                rendermgr;
    frame_t                 framemgr;
    player_t                playermgr;
    enemies_t               enemymgr;
    projectiles_t           projectilemgr;
} game_t;

void InitGame(game_t *gamemgr);
void RunGame(game_t *gamemgr);
void ShutdownGame(game_t *gamemgr);

#endif