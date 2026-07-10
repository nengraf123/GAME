#include <raylib.h>
#include <raymath.h>

class Player {
public:
  void init() {
    PlayerW = 100;
    PlayerH = 100;
    PlayerX = ((double)GetScreenWidth()/2.0f) - ((double)PlayerW/2.0f);
    PlayerY = ((double)GetScreenHeight()/2.0f) - ((double)PlayerH/2.0f);
    // PlayerColor = {0, 200, 180, 255};
    PlayerTexture = LoadTexture("img/face.png");
    PlayerColor = WHITE;
  };
  void logica(float dt) {
    Vector2 movement = { 0.0f, 0.0f };

    // Собираем направление движения
    if (IsKeyDown(KEY_W)) movement.y -= 1.0f;
    if (IsKeyDown(KEY_S)) movement.y += 1.0f;
    if (IsKeyDown(KEY_A)) movement.x -= 1.0f;
    if (IsKeyDown(KEY_D)) movement.x += 1.0f;

    // Проверяем, нажата ли хоть одна клавиша (чтобы не делить на ноль при нормализации)
    if (movement.x != 0.0f || movement.y != 0.0f) {
        // Делаем длину вектора равной 1, сохраняя направление
        movement = Vector2Normalize(movement);
    }

    // Рассчитываем и прибавляем смещение к координатам
    PlayerX += movement.x * PlayerSpeed * dt;
    PlayerY += movement.y * PlayerSpeed * dt;
  }
  void draw() {
    // DrawRectangle(PlayerX, PlayerY, PlayerW, PlayerH, PlayerColor);
    // DrawTexture(PlayerTexture, PlayerX, PlayerY, PlayerColor);
    // 100 / 32 = 3.125f
    float scale = (float)PlayerW / PlayerTexture.width; 
    DrawTextureEx(PlayerTexture, Vector2{(float)PlayerX, (float)PlayerY}, 0.0f, scale, PlayerColor);
  };
  void unload() {
    UnloadTexture(PlayerTexture);
  }
private:
  int PlayerW;
  int PlayerH;
  double PlayerX;
  double PlayerY;
  Color PlayerColor;
  Texture2D PlayerTexture;
  float PlayerSpeed = 500.0f;
};
