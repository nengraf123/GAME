#include "APP.h"
#include <raylib.h>
#include "TextureScale.h"
#include "lib.h"

#define jmp goto
using namespace std;

float X_  = 200, Y_  = 200, W_  = 200,  H_ = 200;
float X2_ = 200, Y2_ = 200, W2_ = 200, H2_ = 200;

void APP::While() {
  player.init();
  // регистрируем камни
  // int stone1 = Hitbox::addStatic(Hitbox(Vector2{X_, Y_},  Vector2{W_,  H_}));
  // int stone2 = Hitbox::addStatic(Hitbox(Vector2{X2_, Y2_}, Vector2{W2_, H2_}));

  panel.init();
  world.init();
  zombie.init();
  egor.init();
  stone.resize(15);
  stone[0].init(100, -100);
  stone[1].init(200, -100);
  stone[2].init(300, -100);
  stone[3].init(400, -100);
  stone[4].init(400, 0);
  stone[5].init(100, 100);
  stone[6].init(200, 100);
  stone[7].init(400, 100);
  stone[8].init(200, 200);
  stone[9].init(400, 200);

  // Texture2D stone = LoadTexture("img/stone.png");

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
      ClearBackground(Color{123, 123, 123, 255});
      camera.target = Vector2Add(player.getPosition(), Vector2Scale(player.getSize(), 0.5f));
      camera.offset = Vector2{ (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
      BeginMode2D(camera);
        world.logica(dt);
        world.draw(camera);

        zombie.logica(dt, player.getPosition(), player.getSize());
        zombie.draw();

        egor.logica(dt, player.getPosition(), player.getSize(), camera);
        egor.draw(player.getPosition(), player.getSize());

        for (auto& s : stone) s.draw();   // в цикле только рисуем

        player.logica(dt);
        player.draw();
      EndMode2D();

      panel.logica(dt);
      panel.draw();
      zombie.drawUI();

      DrawFPS(10, 10);
    EndDrawing();
  }

  player.unload();
  panel.unload();
  world.unload();
  zombie.unload();
  egor.unload();
  // stone.unload();
  // UnloadTexture(stone);
  CloseWindow();
}
// DrawTextureScaled(stone, X_, Y_, W_, H_);
// if (X_ <= 1520) X_ = X_ + 500 * dt;
// Hitbox::getStatic(stone1).setPosition(Vector2{X_, Y_}); // обновляем позицию, не создаём заново
//
// DrawTextureScaled(stone, X2_, Y2_, W2_, H2_);
// X2_ = X2_ - 200 * dt;
// Hitbox::getStatic(stone2).setPosition(Vector2{X2_, Y2_});
