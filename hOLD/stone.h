#pragma once
#include <raylib.h>
#include "TextureScale.h"
#include "hitbox.h"

class Stone {
public:
  Vector2 getPosition() const { return { X, Y }; }
  Vector2 getSize() const { return { W, H }; }

  void init(float x, float y, float w = 100, float h = 100) {
    stone = LoadTexture("img/stone.png");
    X = x; Y = y; W = w; H = h;
    hitbox.set({X, Y}, {W, H});
    Hitbox::addStatic(hitbox); // регистрируем как статичное препятствие ОДИН РАЗ
  }

  void draw() {
    DrawTextureScaled(stone, X, Y, W, H);
  }

  void unload() {
    UnloadTexture(stone);
  }

private:
  Texture2D stone;
  float X = 0, Y = 0, W = 100, H = 100;
  Hitbox hitbox;
};
