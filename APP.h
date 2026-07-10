#pragma once
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "player/Player.h"

const int VIRTUAL_WIDTH = 1920;
const int VIRTUAL_HEIGHT = 1080;

class APP {
public:
  void Start();
  void While();
private:
  Player player;
};
