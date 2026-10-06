#include "APP.h"

using namespace std;

void APP::While() {
  player.init();

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
      ClearBackground(Color{123, 123, 123, 255});
      camera.target = Vector2Add(player.getPosition(), Vector2Scale(player.getSize(), 0.5f));
      camera.offset = Vector2{ (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
      BeginMode2D(camera);
        player.logica(dt);
        player.draw();
      EndMode2D();


      DrawFPS(10, 10);
    EndDrawing();
  }

  player.unload();
  CloseWindow();
}
