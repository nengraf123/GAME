#pragma once
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "hitbox.h"
#include "player/Player.h"
#include "panel.h"
#include "world/world.h"
#include "enemy/zombie.h"
#include "egor.h"
#include "stone.h"


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
