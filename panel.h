#include "lib.h"
#include <raylib.h>

class Panel {
public:
  void init() {
    panelB = false;
  }
  void logica(float dt) {
    if (IsKeyPressed(KEY_TAB)) panelB = !panelB;
  }
  void draw() {
    if (panelB)
      DrawRectangle(100, 100, MONITOR_WIDTH - 200,MONITOR_HEIGHT - 200, Color {123, 123, 123, 200});
  }
private:
  bool panelB;
};
