#pragma once
#include <raylib.h>
#include <raymath.h>
#include "../TextureScale.h"
#include "../lib.h"
#include <vector>
#include "../hitbox.h"

class Zombie {
public:
  Vector2 getPosition() const { return { X, Y }; }
  Vector2 getSize() const { return { W, H }; }
  const Hitbox& getHitbox() const { return hitbox; }

  void setPosition(Vector2 pos) {
    X = pos.x;
    Y = pos.y;
  }
  void init() {
    zombieTex = LoadTexture("img/zombie.png");
    X = -300;
    Y = -300;
    zombieDie = false;
    hitbox.set(getPosition(), getSize());
  }

  // Двигаем зомби, проверяем столкновение с игроком, показываем окно "убить?"
  void logica(float dt, Vector2 playerPos, Vector2 playerSize) {
    if (zombieDie) {
      if (IsKeyPressed(KEY_ONE)) zombieDie = false; // респавн/сброс
      return;
    }

    Vector2 zombiePos = { X, Y };
    Vector2 dir = Vector2Subtract(playerPos, zombiePos);

    if (Vector2Length(dir) > 1.0f) {
      dir = Vector2Normalize(dir);
      X += dir.x * speed * dt;
      Y += dir.y * speed * dt;
    }

    // не даём зомби проходить сквозь камни и прочие статичные препятствия
    hitbox.setPosition({ X, Y });
    Hitbox::resolveAgainstAllStatic(hitbox);
    X = hitbox.getPosition().x;
    Y = hitbox.getPosition().y;


    if (checkCollision(playerPos, playerSize)) {
      if (IsKeyPressed(KEY_ENTER)) zombieDie = true;
      showPrompt = true;
    } else {
      showPrompt = false;
    }
  }

  // Отрисовка самого зомби (только в мировых координатах, внутри BeginMode2D)
  void draw() {
    if (!zombieDie) {
      DrawTextureScaled(zombieTex, X, Y, W, H);
    }
  }

  // Отрисовка UI-окошка "убить зомби?" (в экранных координатах, вне BeginMode2D)
  void drawUI() {
    if (!zombieDie && showPrompt) {
      DrawRectangle(MONITOR_WIDTH/2-500/2, (MONITOR_HEIGHT/2-250/2)+400, 500, 250, WHITE);
      DrawText("Kill zombie?", MONITOR_WIDTH/2-500/2+10, (MONITOR_HEIGHT/2-250/2)+400, 50, BLACK);
      DrawText("YES/NO", MONITOR_WIDTH/2-500/2+10, (MONITOR_HEIGHT/2-250/2)+400+50, 50, BLACK);
    }
  }

  bool checkCollision(Vector2 playerPos, Vector2 playerSize) {
    Rectangle zombieRect = { X, Y, W, H };
    Rectangle playerRect = { playerPos.x, playerPos.y, playerSize.x, playerSize.y };
    return CheckCollisionRecs(zombieRect, playerRect);
  }

  bool isDead() const { return zombieDie; }

  void unload() {
    UnloadTexture(zombieTex);
  }

private:
  Texture2D zombieTex;
  float X;
  float Y;
  float W = 100;
  float H = 100;
  float speed = 200.0f;
  bool zombieDie = false;
  bool showPrompt = false;
  Hitbox hitbox;
};
