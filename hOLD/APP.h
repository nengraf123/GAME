#pragma once
#include <iostream>
#include <raylib.h>
#include <raymath.h>


class APP {
public:
  void Start();
  void While();
private:
  Player player;
  Panel panel;
  World world;
  Zombie zombie;
  Egor egor;
  Hitbox hitbox;
  // Stone stone;
  std::vector<Stone> stone;
  Camera2D camera;
};
