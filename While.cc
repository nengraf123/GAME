#include "APP.h"
#include <raylib.h>

#define jmp goto

using namespace std;


int X_ = 200, Y_ = 200, W_ = 200, H_ = 200;

void APP::While() {

  player.init();
  panel.init();

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    BeginDrawing();
      ClearBackground(WHITE);
      camera.target = Vector2Add(player.getPosition(), Vector2Scale(player.getSize(), 0.5f));
      camera.offset = Vector2{ (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
      BeginMode2D(camera);
        // обьекты которые приикреплены к миру (кроме игрока, камера двигается за ним)
        DrawRectangle(X_, Y_, W_, H_, BLUE); 
        if (X_ == 1520) X_=X_-10;
        if (X_ != 1520) X_=X_+10;
        player.logica(dt);
        player.draw();
      EndMode2D(); // Конец режима камеры
      // обьекты которые прикреплены к монитору (например панель)
      panel.draw();
      panel.logica(dt);
    EndDrawing();
  }
  player.unload();
  CloseWindow();
}
