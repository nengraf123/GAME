#include "APP.h"
#include <raylib.h>

#define jmp goto

using namespace std;


bool init = false;

int H = 200;

void APP::While() {

  player.init();
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    BeginDrawing();
      ClearBackground(WHITE);

      DrawRectangle(200, 200, 200, H, BLUE); 
      DrawFPS(10, 10);
      H--;

      player.logica(dt);
      player.draw();


    EndDrawing();
  }
  CloseWindow();
}















// #include "APP.h"
// #include <raylib.h>
//
// #define jmp goto
//
// using namespace std;
//
// bool HuinyaB = true;
// bool PlayerB = true;
//
// bool initPlayer = false;
//
// int H = 200;
//
// void APP::While() {
//
//   while (!WindowShouldClose()) {
//     float dt = GetFrameTime();
//     BeginDrawing();
//     jmp DrawM;
//
//     HuinyaM:
//       ClearBackground(BLACK);
//       DrawRectangle(200, 200, 200, H, BLUE);  // Теперь квадрат не двигается
//       DrawFPS(10, 10);
//       H--;
//       HuinyaB = false;
//       jmp DrawM;
//
//     PlayerM:
//       if (!initPlayer) {player.init(); initPlayer = true;}
//       player.logica(dt);
//       player.draw();
//       PlayerB = false;
//       jmp DrawM;
//
//
//     DrawM:
//         if (HuinyaB) 
//           jmp HuinyaM;
//         if (PlayerB) 
//           jmp PlayerM;
//     EndDrawing();
//     HuinyaB = true;
//     PlayerB = true;
//   }
//   CloseWindow();
// }
//
//
