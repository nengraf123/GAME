#pragma once
#include <raylib.h>
#include <raymath.h>
#include "../TextureScale.h"
#include "../hitbox.h"

class Player {
public:
  Vector2 getPosition() const { return Vector2{(float)PlayerX, (float)PlayerY}; }
  Vector2 getSize() const { return Vector2{(float)PlayerW, (float)PlayerH}; }
  const Hitbox& getHitbox() const { return hitbox; }

  void init() {
    PlayerW = 100;
    PlayerH = 100;
    PlayerX = 0;
    PlayerY = 0;
    PlayerColor = WHITE;
    PlayerTextureFace = LoadTexture("img/face.png");
    PlayerTextureSide = LoadTexture("img/Side.png");
    PlayerTextureAss  = LoadTexture("img/ass.png");
    hitbox.set(getPosition(), getSize());
  }

  void logica(float dt) {
    if (IsKeyPressed(KEY_G)) autoWalkLeft = !autoWalkLeft;

    Vector2 dir = { 0.0f, 0.0f };

    if (autoWalkLeft) {
      dir.x = -1.0f;
      PlayerX += -200.0f * dt;
      updateFacing(dir);
      return; // выходим, обычное управление ниже не нужно
    }

    if (IsKeyDown(KEY_A)) dir.x -= 1.0f;
    if (IsKeyDown(KEY_D)) dir.x += 1.0f;
    if (IsKeyDown(KEY_W)) dir.y -= 1.0f;
    if (IsKeyDown(KEY_S)) dir.y += 1.0f;

    if (dir.x != 0.0f || dir.y != 0.0f) {
      dir = Vector2Normalize(dir);
      PlayerX += dir.x * PlayerSpeed * dt;
      PlayerY += dir.y * PlayerSpeed * dt;
    }

    updateFacing(dir);
    hitbox.setPosition(getPosition());
    Hitbox::resolveAgainstAllStatic(hitbox);
    PlayerX = hitbox.getPosition().x;
    PlayerY = hitbox.getPosition().y;
  }

  void draw() {
    Texture2D tex;
    if (facing == Facing::Side)      tex = PlayerTextureSide;
    else if (facing == Facing::Up)   tex = PlayerTextureAss;
    else                             tex = PlayerTextureFace;

    bool flipX = (facing == Facing::Side && !facingLeft);
    DrawTextureScaled(tex, (float)PlayerX, (float)PlayerY, (float)PlayerW, (float)PlayerH, PlayerColor, flipX);
  }

  void unload() {
    UnloadTexture(PlayerTextureFace);
    UnloadTexture(PlayerTextureSide);
    UnloadTexture(PlayerTextureAss);
  }
  void setPosition(Vector2 pos) {
    PlayerX = pos.x;
    PlayerY = pos.y;
  }

private:
  enum class Facing { Down, Up, Side };

  void updateFacing(Vector2 dir) {
    if (dir.x != 0.0f) {
      facing = Facing::Side;
      facingLeft = dir.x < 0.0f;
    } else if (dir.y < 0.0f) {
      facing = Facing::Up;
    } else if (dir.y > 0.0f) {
      facing = Facing::Down;
    }
  }

  int PlayerW;
  int PlayerH;
  double PlayerX;
  double PlayerY;
  Color PlayerColor;
  double PlayerSpeed = 500.0f;

  Texture2D PlayerTextureFace;
  Texture2D PlayerTextureSide;
  Texture2D PlayerTextureAss;

  Facing facing = Facing::Down;
  bool facingLeft = false;
  bool autoWalkLeft = false;

  Hitbox hitbox;
};
