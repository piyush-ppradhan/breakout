#pragma once
#include "raylib.h"

class Brick {
public:
  Vector2 corner_pos;
  bool destroyed;
  Brick();
  Brick(bool destroyed, int i, int j);
  void draw_brick();
  int check_collision(Vector2 ball_pos);
};
