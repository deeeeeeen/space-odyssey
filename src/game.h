#ifndef GAME_H
#define GAME_H

#include "settings.h"
#include "main-menu.h"
#include "state.h"
#include "render.h"
#include "frame.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "physics.h"
#include "logger.h"
#include "audio.h"
#include "font.h"
#include <time.h>
#include <string.h>

#define GAME_TITLE         "it was no-one"

typedef struct state_s              state_t;
typedef struct mainmenu_s           mainmenu_t;
typedef struct render_s             render_t;
typedef struct player_s             player_t;
typedef struct enemygroup_s         enemygroup_t;
typedef struct frame_s              frame_t;
typedef struct projectilegroup_s    projectilegroup_t;

typedef struct game_s {
    state_t                 statemgr;
    render_t                rendermgr;
    frame_t                 framemgr;
    player_t                playermgr;
    enemygroup_t            enemymgr;
    projectilegroup_t       projectilemgr;
} game_t;

void LoadGameSave(game_t *gamemgr);

void InitGame(game_t *gamemgr);
void RunGame(game_t *gamemgr);
void ShutdownGame(game_t *gamemgr);

#endif