#pragma once
#include "brick.hpp"
#include "config.hpp"

class Breakout {
private:
  int height;
  int width;
  Brick bricks[nrows][ncols];

public:
  Breakout();
  void run();
  void check_collisions(Vector2 ball_pos, Vector2 &ball_velocity);
  void check_completion(bool &completed);
  void close();
};
