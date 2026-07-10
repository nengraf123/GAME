#include "APP.h"
#include <raylib.h>

#define jmp goto

using namespace std;


bool init = false;

int X_ = 200, Y_ = 200, W_ = 200, H_ = 200;

void APP::While() {

  player.init();

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    BeginDrawing();
      ClearBackground(WHITE);

      DrawRectangle(X_, Y_, W_, H_, BLUE); 
      DrawFPS(10, 10);
      if (X_ == 1520) X_=X_-10;
      if (X_ != 1520) X_=X_+10;

      player.logica(dt);
      player.draw();


    EndDrawing();
  }
  CloseWindow();
}
