#pragma once
#include "lib.h"
#include <raylib.h>
#include "TextureScale.h"


class Panel {
public:
  void init() {
    panelB = false;
    tab = LoadTexture("img/tab.png");
  }
  void logica(float dt) {
    if (IsKeyPressed(KEY_TAB)) panelB = !panelB;
  }
  void draw() {
    if (panelB)
      DrawTextureScaled(tab, 100, 100, MONITOR_WIDTH - 200,MONITOR_HEIGHT - 200);
  }
  void unload() {
    UnloadTexture(tab);
  }
private:
  bool panelB;
  Texture2D tab;
};
