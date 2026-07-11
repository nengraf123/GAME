#pragma once
#include <raylib.h>

inline void DrawTextureScaled(Texture2D tex, float x, float y, float w, float h, Color color = WHITE, bool flipX = false) {
  // Если flipX равен true, делаем ширину исходного прямоугольника отрицательной
  float srcWidth = flipX ? -(float)tex.width : (float)tex.width;
  
  Rectangle src = { 0.0f, 0.0f, srcWidth, (float)tex.height };
  Rectangle dst = { x, y, w, h };
  DrawTexturePro(tex, src, dst, Vector2{0, 0}, 0.0f, color);
}
// inline void DrawTextureScaled(Texture2D tex, float x, float y, float w, float h, Color color = WHITE) {
//   Rectangle src = { 0.0f, 0.0f, (float)tex.width, (float)tex.height };
//   Rectangle dst = { x, y, w, h };
//   DrawTexturePro(tex, src, dst, Vector2{0, 0}, 0.0f, color);
// }
