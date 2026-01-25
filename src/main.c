#include "game.h"

int main()
{
    static game_t gamemgr;
    InitGame(&gamemgr);
    RunGame(&gamemgr);
    ShutdownGame(&gamemgr);
}