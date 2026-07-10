#pragma once
#include <raylib.h>
#include <algorithm>

class Viewport {
public:
    Viewport(int virtualWidth, int virtualHeight) 
        : virtualWidth(virtualWidth), virtualHeight(virtualHeight) {
        // Конструктор больше не загружает текстуру
    }

    // Инициализация текстуры (вызывается после InitWindow)
    void Init() {
        target = LoadRenderTexture(virtualWidth, virtualHeight);
    }

    ~Viewport() {
        if (target.texture.id != 0) {
            UnloadRenderTexture(target);
        }
    }

    void Begin() {
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);
    }

    void End() {
        EndTextureMode();
    }

    void Draw() {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        float scale = std::min(
            (float)screenWidth / virtualWidth, 
            (float)screenHeight / virtualHeight
        );
        
        float drawWidth = virtualWidth * scale;
        float drawHeight = virtualHeight * scale;
        
        float offsetX = (screenWidth - drawWidth) / 2.0f;
        float offsetY = (screenHeight - drawHeight) / 2.0f;

        DrawTexturePro(
            target.texture,
            {0, 0, (float)virtualWidth, (float)-virtualHeight},
            {offsetX, offsetY, drawWidth, drawHeight},
            {0, 0}, 0.0f, WHITE
        );
    }

private:
    int virtualWidth;
    int virtualHeight;
    RenderTexture2D target{};
};
