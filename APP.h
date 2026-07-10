#pragma once
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "player/Player.h"

const int MONITOR_WIDTH = 1920;
const int MONITOR_HEIGHT = 1080;

class APP {
public:
  void Start();
  void While();
private:
  Player player;
};
