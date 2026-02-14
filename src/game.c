#include "game.h"

#ifdef _WIN32
    #include <process.h>
    #define getpid _getpid
#else
    #include <unistd.h>
#endif

void GenerateRandomSeed();
void LoadGameSave(game_t *gamemgr);

void InitGameWindow(game_t *gamemgr) {
    memset(gamemgr, ZERO, sizeof(game_t));
    SetTraceLogCallback(ColorLog);
    GenerateRandomSeed();
    
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(ZERO, ZERO, GAME_TITLE);
    DisableCursor();
    
    InitSettings();
    if (DoesSettingsFileExist()) {
        LoadGameSave(gamemgr);
    }
}

void InitGame(game_t *gamemgr) {
    InitGameWindow(gamemgr);
    InitFont();
    AudioInit();
    InitRender(&gamemgr->rendermgr);
    InitPlayer(&gamemgr->playermgr);
    InitEnemy(&gamemgr->enemymgr);
    InitFrame(&gamemgr->framemgr);
}

void RunGame(game_t *gamemgr) {
    while (gamemgr->statemgr.state != EXIT)
    {
        FrameUpdateDelta();
        switch (gamemgr->statemgr.state) {
            case TITLE_SCREEN:
                UpdateMainMenuCursor(&gamemgr->statemgr, &gamemgr->rendermgr.main_menu);
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
                UpdatePauseMenuCursor(&gamemgr->statemgr, &gamemgr->rendermgr.gui.pause_menu);
                RenderPauseMenu(&gamemgr->rendermgr, &gamemgr->framemgr, &gamemgr->playermgr, &gamemgr->enemymgr, &gamemgr->projectilemgr);
                break;
        }
    }
}

void ShutdownGame(game_t *gamemgr) {
    AudioShutdown();
    CloseWindow();
}

void GenerateRandomSeed() {
    SetRandomSeed((unsigned int)time(NULL) ^ ((unsigned int)getpid() << 16));
    TraceLog(LOG_INFO, "RENDER: Random has been seeded!");
}

void LoadGameSave(game_t *gamemgr) {
    
}