#include <raylib.h>
#include <raymath.h>

class Player {
public:
  Vector2 getPosition() const { return Vector2{(float)PlayerX, (float)PlayerY}; }
  Vector2 getSize() const { return Vector2{(float)PlayerW, (float)PlayerH}; }
  void init() {
    PlayerW = 100;
    PlayerH = 100;
    PlayerX = ((double)GetScreenWidth()/2.0f) - ((double)PlayerW/2.0f);
    PlayerY = ((double)GetScreenHeight()/2.0f) - ((double)PlayerH/2.0f);
    // PlayerColor = {0, 200, 180, 255};
    PlayerTextureFace = LoadTexture("img/face.png");
    PlayerTextureSide = LoadTexture("img/Side.png");
    PlayerTextureAss = LoadTexture("img/ass.png");
    PlayerColor = WHITE;
  };
  void logica(float dt) {
    Vector2 movement = { 0.0f, 0.0f };
    if (IsKeyDown(KEY_W)) movement.y -= 1.0f;
    if (IsKeyDown(KEY_S)) movement.y += 1.0f;

    if (IsKeyDown(KEY_A)) { movement.x -= 1.0f; isSide = true; facingLeft = true; }
    if (IsKeyDown(KEY_D)) { movement.x += 1.0f; isSide = true; facingLeft = false; }
    isUp = IsKeyDown(KEY_W);

    if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) isSide = false; // сброс, только если бок не зажат

    if (movement.x != 0.0f || movement.y != 0.0f)
        movement = Vector2Normalize(movement);

    PlayerX += movement.x * PlayerSpeed * dt;
    PlayerY += movement.y * PlayerSpeed * dt;
  }
  void draw() {
    Texture2D tex = isSide ? PlayerTextureSide : (isUp ? PlayerTextureAss : PlayerTextureFace);
    float scale = (float)PlayerW / tex.width;

    Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
    if (isSide && !facingLeft) {
        src.width = -src.width; // инверсия по X, когда идём вправо
    }

    Rectangle dst = { (float)PlayerX, (float)PlayerY, (float)PlayerW, (float)PlayerH };
    DrawTexturePro(tex, src, dst, Vector2{0, 0}, 0.0f, PlayerColor);
  };
  void unload() {
    UnloadTexture(PlayerTextureFace);
    UnloadTexture(PlayerTextureSide);
    UnloadTexture(PlayerTextureAss);
  }
private:
  int PlayerW;
  int PlayerH;
  double PlayerX;
  double PlayerY;
  Color PlayerColor;
  double PlayerSpeed = 500.0f;
  Texture2D PlayerTextureFace;
  Texture2D PlayerTextureSide;
  Texture2D PlayerTextureAss;
  bool isSide = false;
  bool facingLeft = false;
  bool isUp = false;
};
