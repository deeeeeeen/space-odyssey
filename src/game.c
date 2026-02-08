#include "game.h"

#ifdef _WIN32
    #include <process.h>
    #define getpid _getpid
#else
    #include <unistd.h>
#endif

Font dfont;

void GenerateRandomSeed();

void InitGameWindow(game_t *gamemgr) {
    memset(gamemgr, ZERO, sizeof(game_t));
    SetTraceLogCallback(ColorLog);
    GenerateRandomSeed();

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(ZERO, ZERO, GAME_TITLE);
    SetTargetFPS(GAME_FPS);
    DisableCursor();

    dfont = LoadFontEx("res/PIXEARG_.ttf", 11, ((void*)ZERO), ZERO);
    SetTextureFilter(dfont.texture, TEXTURE_FILTER_POINT);
}

void InitGame(game_t *gamemgr) {
    InitGameWindow(gamemgr);
    InitRender(&gamemgr->rendermgr);
    InitPlayer(&gamemgr->playermgr);
    InitEnemy(&gamemgr->enemymgr);
    InitFrame(&gamemgr->framemgr);
}

void RunGame(game_t *gamemgr) {
    while (gamemgr->statemgr.state != EXIT)
    {
        switch (gamemgr->statemgr.state) {
            case TITLE_SCREEN:
                UpdateCursor(&gamemgr->statemgr, &gamemgr->rendermgr.main_menu);
                RenderTitle(&gamemgr->rendermgr, &gamemgr->framemgr, &gamemgr->playermgr);
                FadeAwayTitle(&gamemgr->rendermgr.main_menu);
                StartGame(&gamemgr->statemgr, &gamemgr->rendermgr.main_menu, &gamemgr->playermgr);
                EndGame(&gamemgr->statemgr, &gamemgr->playermgr);
                break;
            case GAME:
                UpdatePlayer(&gamemgr->playermgr, &gamemgr->projectilemgr);
                if (WaitUntilCombatStarts(&gamemgr->rendermgr.cutscene)) {
                    UpdateEnemy(&gamemgr->enemymgr, &gamemgr->projectilemgr);
                    UpdateProjectiles(&gamemgr->projectilemgr);
                    ProjectileCollMgr(&gamemgr->projectilemgr, &gamemgr->enemymgr, &gamemgr->playermgr);
                }
                RenderWindow(&gamemgr->rendermgr, &gamemgr->framemgr, &gamemgr->playermgr, &gamemgr->enemymgr, &gamemgr->projectilemgr);
                EndGame(&gamemgr->statemgr, &gamemgr->playermgr);
                break;
            case PAUSE:
                // TODO: draw gui while everything else is frozen
                // ---
                RenderWindow(&gamemgr->rendermgr, &gamemgr->framemgr, &gamemgr->playermgr, &gamemgr->enemymgr, &gamemgr->projectilemgr);
                break;
        }
    }
}

void ShutdownGame(game_t *gamemgr) {
    CloseWindow();
}

void GenerateRandomSeed() {
    SetRandomSeed((unsigned int)time(NULL) ^ ((unsigned int)getpid() << 16));
    TraceLog(LOG_INFO, "RENDER: Random has been seeded!");
}