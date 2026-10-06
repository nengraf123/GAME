#include <string>
#include <raylib.h>

void Entity(const char* TxtFace, const char* TxtSide, const char* TxtAss);

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(1920, 1080, "float");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
      ClearBackground(Color{123, 123, 123, 255});
      DrawFPS(10, 10);
      Entity("img/face.png", "img/Side.png", "img/ass.png");
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void Entity (const char* TxtFace, const char* TxtSide, const char* TxtAss) {
    Texture2D TextureFace = LoadTexture(TxtFace);
    Texture2D TextureSide = LoadTexture(TxtSide);
    Texture2D TextureAss  = LoadTexture(TxtAss);
}
