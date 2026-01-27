#include "game.h"

#ifdef _WIN32
    #include <process.h>
    #define getpid _getpid
#else
    #include <unistd.h>
#endif

void GenerateRandomSeed();

void InitGameWindow(game_t *gamemgr) {
    memset(gamemgr, 0, sizeof(game_t));
    SetTraceLogCallback(ColorLog);
    GenerateRandomSeed();

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, GAME_TITLE);
    SetTargetFPS(GAME_FPS);
    DisableCursor();
}

void InitGame(game_t *gamemgr) {
    InitGameWindow(gamemgr);
    InitRender(&gamemgr->rendermgr);
    InitPlayer(&gamemgr->playermgr);
    InitEnemy(&gamemgr->enemymgr);
    InitFrame(&gamemgr->framemgr);
}

void RunGame(game_t *gamemgr) {
    while (!WindowShouldClose())
    {
        UpdatePlayer(&gamemgr->playermgr, &gamemgr->projectilemgr);   
        UpdateEnemy(&gamemgr->enemymgr, &gamemgr->projectilemgr);
        UpdateProjectiles(&gamemgr->projectilemgr);
        ProjectileCollMgr(&gamemgr->projectilemgr, &gamemgr->enemymgr, &gamemgr->playermgr);
        RenderWindow(&gamemgr->rendermgr, &gamemgr->framemgr, &gamemgr->playermgr, &gamemgr->enemymgr, &gamemgr->projectilemgr);
    }
}

void ShutdownGame(game_t *gamemgr) {
    CloseWindow();
}

void GenerateRandomSeed() {
    SetRandomSeed((unsigned int)time(NULL) ^ ((unsigned int)getpid() << 16));
    TraceLog(LOG_INFO, "RENDER: Random has been seeded!");
}