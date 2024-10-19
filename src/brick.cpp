#include "brick.hpp"
#include "config.hpp"

Brick::Brick() {
  this->destroyed = false;
  this->corner_pos.x = 0.0;
  this->corner_pos.y = 0.0;
}

Brick::Brick(bool destroyed, int i, int j) {
  this->destroyed = destroyed;
  this->corner_pos.x = i * (brick_dims[0] + brick_space) + top_padding[0];
  this->corner_pos.y = j * (brick_dims[1] + brick_space) + top_padding[1];
}

void Brick::draw_brick() {
  if (!this->destroyed) {
    DrawRectangleV(this->corner_pos, Vector2({brick_dims[0], brick_dims[1]}),
                   GREEN);
  }
}

int Brick::check_collision(Vector2 ball_pos) {
  // y collision
  float collision_dist = 0.0f;
  float dist = 0.0f;
  if (ball_pos.y < this->corner_pos.y) {
    collision_dist = brick_dims[1] + ball_radius;
    dist = (this->corner_pos.y) - ball_pos.y;
    if ((ball_pos.x >= this->corner_pos.x) &&
        (ball_pos.x <= this->corner_pos.x + brick_dims[0])) {
      if ((dist <= collision_dist) && (!this->destroyed))
        return 1;
    }
  }
  if (ball_pos.y >= this->corner_pos.y) {
    collision_dist = ball_radius;
    dist = ball_pos.y - (this->corner_pos.y);
    if ((ball_pos.x >= this->corner_pos.x) &&
        (ball_pos.x <= this->corner_pos.x + brick_dims[0])) {
      if ((dist <= collision_dist) && (!this->destroyed))
        return 1;
    }
  }

  // x collision
  if (ball_pos.x < this->corner_pos.x) {
    collision_dist = ball_radius;
    dist = (this->corner_pos.x) - ball_pos.x;
    if ((ball_pos.y >= this->corner_pos.y) &&
        (ball_pos.y <= this->corner_pos.y + brick_dims[1])) {
      if ((dist <= collision_dist) && (!this->destroyed))
        return 1;
    }
  }
  if (ball_pos.x >= this->corner_pos.x) {
    collision_dist = ball_radius + brick_dims[0];
    dist = ball_pos.x - (this->corner_pos.x);
    if ((ball_pos.y >= this->corner_pos.y) &&
        (ball_pos.y <= this->corner_pos.y + brick_dims[1])) {
      if ((dist <= collision_dist) && (!this->destroyed))
        return 1;
    }
  }
  return 0;
}
