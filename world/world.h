#pragma once
#include "../TextureScale.h"
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <cmath>


class World {
public:
  static const int CHUNK_SIZE = 16;
  static const int TILE_SIZE = 100;

  void init() {
    grass = LoadTexture("img/grass.png");
    stone = LoadTexture("img/stone.png");
  }

  // Рисуем только тайлы, попавшие в видимую область камеры
  void draw(Camera2D camera) {
    Vector2 topLeft = GetScreenToWorld2D(Vector2{0, 0}, camera);
    Vector2 bottomRight = GetScreenToWorld2D(
        Vector2{(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

    int startX = (int)floorf(topLeft.x / TILE_SIZE) - 1;
    int startY = (int)floorf(topLeft.y / TILE_SIZE) - 1;
    int endX   = (int)floorf(bottomRight.x / TILE_SIZE) + 1;
    int endY   = (int)floorf(bottomRight.y / TILE_SIZE) + 1;

    for (int y = startY; y <= endY; y++) {
      for (int x = startX; x <= endX; x++) {
        int tile = getTile(x, y);
        float posX = x * (float)TILE_SIZE;
        float posY = y * (float)TILE_SIZE;
        Texture2D tex = (tile == 1) ? stone : grass;
        DrawTextureScaled(tex, posX, posY, TILE_SIZE, TILE_SIZE);
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

  struct Chunk {
    int tiles[CHUNK_SIZE * CHUNK_SIZE];
  };

  std::unordered_map<long long, Chunk> chunks;

  static long long chunkKey(int cx, int cy) {
    return ((long long)(unsigned int)cx << 32) | (unsigned int)(unsigned int)cy;
  }

  // Детерминированный "хэш-шум" по координатам тайла
  static float hashNoise(int x, int y, int seed = 1000) { // 1337
    int n = x * 374761393 + y * 668265263 + seed * 69069;
    n = (n ^ (n >> 13)) * 1274126177;
    n = n ^ (n >> 16);
    return (float)(n & 0x7fffffff) / (float)0x7fffffff; // 0..1
  }

  // Value noise с билинейной интерполяцией между узлами решётки
  static float valueNoise(float x, float y) {
    int x0 = (int)floorf(x), y0 = (int)floorf(y);
    int x1 = x0 + 1, y1 = y0 + 1;
    float sx = x - x0, sy = y - y0;

    float n00 = hashNoise(x0, y0);
    float n10 = hashNoise(x1, y0);
    float n01 = hashNoise(x0, y1);
    float n11 = hashNoise(x1, y1);

    float ix0 = n00 + (n10 - n00) * sx;
    float ix1 = n01 + (n11 - n01) * sx;
    return ix0 + (ix1 - ix0) * sy;
  }

  int generateTileType(int tx, int ty) {
    float scale = 0.05f; // меньше — крупнее "острова" камня
    float n = valueNoise(tx * scale, ty * scale);
    return (n > 0.55f) ? 1 : 0; // 1 = камень, 0 = трава
  }

  Chunk& getChunk(int cx, int cy) {
    long long key = chunkKey(cx, cy);
    auto it = chunks.find(key);
    if (it != chunks.end()) return it->second;

    Chunk chunk;
    for (int ly = 0; ly < CHUNK_SIZE; ly++) {
      for (int lx = 0; lx < CHUNK_SIZE; lx++) {
        int tx = cx * CHUNK_SIZE + lx;
        int ty = cy * CHUNK_SIZE + ly;
        chunk.tiles[ly * CHUNK_SIZE + lx] = generateTileType(tx, ty);
      }
    }
    return chunks.emplace(key, chunk).first->second;
  }

  int getTile(int tx, int ty) {
    int cx = (int)floorf((float)tx / CHUNK_SIZE);
    int cy = (int)floorf((float)ty / CHUNK_SIZE);
    Chunk& chunk = getChunk(cx, cy);
    int lx = tx - cx * CHUNK_SIZE;
    int ly = ty - cy * CHUNK_SIZE;
    return chunk.tiles[ly * CHUNK_SIZE + lx];
  }
};
