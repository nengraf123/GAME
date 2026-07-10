#include "APP.h"

void APP::Start() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1920, 1080, "Game");
    ToggleFullscreen();
    SetTargetFPS(60);
}
