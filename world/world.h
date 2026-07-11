#pragma once
#include "../TextureScale.h"
#include <raylib.h>
#include <vector>

class World {
public:
  void init() {
    grass = LoadTexture("img/grass.png");

    // Размеры огромного мира в блоках
    int mapWidth = 2000;  
    int mapHeight = 2000; 

    // Выделяем память под огромную карту сразу
    map.resize(mapHeight, std::vector<int>(mapWidth, 0));

    // Для теста: заполним границы мира камнем (id 1)
    for (int y = 0; y < mapHeight; y++) {
      for (int x = 0; x < mapWidth; x++) {
        if (x == 0 || y == 0 || x == mapWidth - 1 || y == mapHeight - 1) {
          map[y][x] = 1; 
        }
      }
    }
  }

  // Передаем камеру в метод draw, чтобы знать, что видит игрок
  void draw(Camera2D camera) {
    // 1. Получаем координаты левого верхнего и правого нижнего углов экрана в игровом мире
    Vector2 topLeft = GetScreenToWorld2D(Vector2{ 0, 0 }, camera);
    Vector2 bottomRight = GetScreenToWorld2D(Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() }, camera);

    // 2. Переводим пиксельные координаты в индексы блоков (тайлов)
    int startX = (int)(topLeft.x / tileSize);
    int startY = (int)(topLeft.y / tileSize);
    int endX = (int)(bottomRight.x / tileSize) + 1;
    int endY = (int)(bottomRight.y / tileSize) + 1;

    // 3. Ограничиваем индексы, чтобы не выйти за пределы массива карты
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > map[0].size()) endX = map[0].size();
    if (endY > map.size()) endY = map.size();

    // 4. Рисуем ТОЛЬКО те блоки, которые попали в область видимости
    for (int y = startY; y < endY; y++) {
      for (int x = startX; x < endX; x++) {
        float posX = x * tileSize;
        float posY = y * tileSize;

        if (map[y][x] == 0) {
            DrawTextureScaled(grass, posX, posY, tileSize, tileSize);
        } else if (map[y][x] == 1) {
            DrawTextureScaled(grass, posX, posY, tileSize, tileSize);
        }
      }
    }
  }

  void logica(float dt) {}
  
  void unload() {
    UnloadTexture(grass);
    UnloadTexture(stone);
  }

private:
  Texture2D grass;
  Texture2D stone;
  float tileSize = 100.0f;
  std::vector<std::vector<int>> map;
};
