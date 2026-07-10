#include "APP.h"

void APP::Start() {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // InitWindow(1920, 1080, "Game");
    // ToggleFullscreen();
    // SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1920, 1080, "Game");
    SetTargetFPS(60);
    // Настройка камеры
    camera = { 0 };
    camera.zoom = 1.0f;
    // Сдвиг фокуса в центр экрана
    camera.offset = Vector2{ (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
}
