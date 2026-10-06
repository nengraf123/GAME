#pragma once
#include <raylib.h>
#include <algorithm>
#include <vector>

class Hitbox {
public:
  Hitbox() = default;
  Hitbox(float x, float y, float w, float h) : rect{x, y, w, h} {}
  Hitbox(Vector2 pos, Vector2 size) : rect{pos.x, pos.y, size.x, size.y} {}

  // ---- позиция/размер ----
  void setPosition(Vector2 pos) { rect.x = pos.x; rect.y = pos.y; }
  void setSize(Vector2 size)    { rect.width = size.x; rect.height = size.y; }
  void set(Vector2 pos, Vector2 size) { setPosition(pos); setSize(size); }

  Vector2 getPosition() const { return { rect.x, rect.y }; }
  Vector2 getSize() const     { return { rect.width, rect.height }; }
  const Rectangle& getRect() const { return rect; }

  // ---- коллизии между двумя хитбоксами ----
  bool collidesWith(const Hitbox& other) const {
    return CheckCollisionRecs(rect, other.rect);
  }

  // Выталкивает this за пределы other по наименьшей оси проникновения
  void resolveAgainst(const Hitbox& other) {
    if (!collidesWith(other)) return;

    float overlapX = std::min(rect.x + rect.width, other.rect.x + other.rect.width)
                    - std::max(rect.x, other.rect.x);
    float overlapY = std::min(rect.y + rect.height, other.rect.y + other.rect.height)
                    - std::max(rect.y, other.rect.y);

    if (overlapX < overlapY) {
      if (rect.x < other.rect.x) rect.x -= overlapX;
      else                       rect.x += overlapX;
    } else {
      if (rect.y < other.rect.y) rect.y -= overlapY;
      else                       rect.y += overlapY;
    }
  }

  void draw(Color color = Color{255, 0, 0, 100}) const {
    DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 2.0f, RED);
  }

  // ---- статичный список хитбоксов (камни, стены и т.п.) ----
  // Работает как общий реестр на уровне класса, отдельный "менеджер" не нужен
  static int addStatic(Hitbox hb) {
    staticList.push_back(hb);
    return (int)staticList.size() - 1;
  }
  static void clearStatic() { staticList.clear(); }
  static Hitbox& getStatic(int index) { return staticList[index]; }

  static void resolveAgainstAllStatic(Hitbox& moving) {
    for (auto& hb : staticList) moving.resolveAgainst(hb);
  }
  static void debugDrawStatic() {
    for (auto& hb : staticList) hb.draw();
  }

private:
  Rectangle rect{0, 0, 0, 0};
  static inline std::vector<Hitbox> staticList;
};
