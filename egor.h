#pragma once
#include "TextureScale.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <cstdlib>
#include <cmath>

// Егорушка Анальный
class Egor {
public:
  void init() {
    penis_egora  = LoadTexture("img/penis_egora.png");
    sperma_egora = LoadTexture("img/kaplya_spermy.png");
  }

  void logica(float dt, Vector2 ownerPos, Vector2 ownerSize, Camera2D camera) {
    Vector2 center = Vector2Add(ownerPos, Vector2Scale(ownerSize, 0.5f));
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    Vector2 aimDir = Vector2Subtract(mouseWorld, center);

    if (Vector2Length(aimDir) > 0.0f) {
      aimDir = Vector2Normalize(aimDir);
      aimAngle = atan2f(aimDir.y, aimDir.x); // радианы
    }

    // позиция пушки — по окружности вокруг игрока
    gunPos = Vector2Add(center, Vector2{ cosf(aimAngle) * orbitRadius, sinf(aimAngle) * orbitRadius });

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      shoot(aimAngle);
    }

    for (auto it = bullets.begin(); it != bullets.end(); ) {
      it->pos.x += it->dir.x * bulletSpeed * dt;
      it->pos.y += it->dir.y * bulletSpeed * dt;
      it->life += dt;

      if (it->life > bulletLifetime)
        it = bullets.erase(it);
      else
        ++it;
    }
  }

  void draw(Vector2 ownerPos, Vector2 ownerSize) {
    float angleDeg = aimAngle * RAD2DEG;

    // рисуем пушку с поворотом по направлению прицела
    Rectangle src = { 0, 0, (float)penis_egora.width, (float)penis_egora.height };
    Rectangle dst = { gunPos.x, gunPos.y, gunSize, gunSize };
    Vector2 origin = { gunSize / 2, gunSize / 2 };
    DrawTexturePro(penis_egora, src, dst, origin, angleDeg+90, WHITE);

    for (auto& b : bullets) {
      DrawTextureScaled(sperma_egora, b.pos.x - bulletSize / 2, b.pos.y - bulletSize / 2, bulletSize, bulletSize);
    }
  }

  void unload() {
    UnloadTexture(penis_egora);
    UnloadTexture(sperma_egora);
  }

private:
  struct Bullet {
    Vector2 pos;
    Vector2 dir;
    float life;
  };

  void shoot(float baseAngle) {
    float spreadRad = spreadDeg * DEG2RAD;
    for (int i = 0; i < pelletCount; i++) {
      float t = (pelletCount == 1) ? 0.0f : ((float)i / (pelletCount - 1)) - 0.5f; // -0.5..0.5
      float jitter = ((float)rand() / RAND_MAX - 0.5f) * jitterDeg * DEG2RAD;
      float angle = baseAngle + t * spreadRad + jitter;

      Vector2 dir = { cosf(angle), sinf(angle) };
      bullets.push_back(Bullet{ gunPos, dir, 0.0f });
    }
  }

  Texture2D penis_egora;
  Texture2D sperma_egora;
  std::vector<Bullet> bullets;

  Vector2 gunPos = { 0, 0 };
  float aimAngle = 0.0f;

  float gunSize     = 40.0f;   // размер пушки (было 100)
  float orbitRadius = 60.0f;   // радиус вращения вокруг игрока

  int   pelletCount = 6;       // сколько пуль за выстрел
  float spreadDeg   = 35.0f;   // общий угол разброса
  float jitterDeg   = 5.0f;    // случайное дрожание угла на каждую пулю

  float bulletSpeed    = 900.0f;
  float bulletSize     = 20.0f;
  float bulletLifetime = 2.0f;
};
