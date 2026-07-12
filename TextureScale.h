#pragma once
#include <raylib.h>
#include <algorithm>

inline void DrawTextureScaled(Texture2D tex, float x, float y, float w, float h, Color color = WHITE, bool flipX = false) {
  float srcWidth = flipX ? -(float)tex.width : (float)tex.width;
  Rectangle src = { 0.0f, 0.0f, srcWidth, (float)tex.height };
  Rectangle dst = { x, y, w, h };
  DrawTexturePro(tex, src, dst, Vector2{0, 0}, 0.0f, color);
}

// Выталкивает playerRec за пределы otherRec по наименьшей оси проникновения
inline void resolveCollision(Rectangle& playerRec, const Rectangle& otherRec) {
    if (!CheckCollisionRecs(playerRec, otherRec)) return;

    float overlapX = std::min(playerRec.x + playerRec.width, otherRec.x + otherRec.width)
                    - std::max(playerRec.x, otherRec.x);
    float overlapY = std::min(playerRec.y + playerRec.height, otherRec.y + otherRec.height)
                    - std::max(playerRec.y, otherRec.y);

    if (overlapX < overlapY) {
        if (playerRec.x < otherRec.x)
            playerRec.x -= overlapX;
        else
            playerRec.x += overlapX;
    } else {
        if (playerRec.y < otherRec.y)
            playerRec.y -= overlapY;
        else
            playerRec.y += overlapY;
    }
}
// inline void DrawTextureScaled(Texture2D tex, float x, float y, float w, float h, Color color = WHITE, bool flipX = false) {
//   // Если flipX равен true, делаем ширину исходного прямоугольника отрицательной
//   float srcWidth = flipX ? -(float)tex.width : (float)tex.width;
//
//   Rectangle src = { 0.0f, 0.0f, srcWidth, (float)tex.height };
//   Rectangle dst = { x, y, w, h };
//   DrawTexturePro(tex, src, dst, Vector2{0, 0}, 0.0f, color);
// }
// inline void DrawTextureScaled(Texture2D tex, float x, float y, float w, float h, Color color = WHITE) {
//   Rectangle src = { 0.0f, 0.0f, (float)tex.width, (float)tex.height };
//   Rectangle dst = { x, y, w, h };
//   DrawTexturePro(tex, src, dst, Vector2{0, 0}, 0.0f, color);
// }
