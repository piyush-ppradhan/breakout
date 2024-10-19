#include "breakout.hpp"
#include "config.hpp"

Breakout::Breakout() {
  this->width = WIDTH;
  this->height = HEIGHT;

  for (int i = 0; i < nrows; ++i)
    for (int j = 0; j < ncols; ++j) {
      this->bricks[i][j] = Brick(false, i, j);
    }
}

void Breakout::check_collisions(Vector2 ball_pos, Vector2 &ball_velocity) {
  bool exit_loop = false;
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      int res = this->bricks[i][j].check_collision(ball_pos);
      if (res == 1) {
        ball_velocity.y *= -1.0f;
        this->bricks[i][j].destroyed = true;
        exit_loop = true;
        break;
      }
      if (res == 2) {
        ball_velocity.x *= -1.0f;
        this->bricks[i][j].destroyed = true;
        exit_loop = true;
        break;
      }
    }
    if (exit_loop)
      break;
  }
}

void Breakout::check_completion(bool &completed) {
  completed = true;
  bool exit_loop;
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      if (!this->bricks[i][j].destroyed) {
        completed = false;
        exit_loop = true;
        break;
      }
    }
    if (exit_loop)
      break;
  }
}

void Breakout::run() {
  InitWindow(this->width, this->height, "Breakout");

  bool init = true;
  bool completed = false;
  bool lost = false;
  float frac = 0.9;

  Vector2 pad_position = {(float)this->width / 2.0f,
                          frac * (float)this->height};
  Vector2 pad_dims = {pad_dims_x, pad_dims_y};

  pad_position.x -= pad_dims.x / 2.0;
  pad_position.y -= pad_dims.y / 2.0;

  Vector2 ball_pos = {init_ball_pos[0], init_ball_pos[1]};
  Vector2 ball_velocity = {0.0f, gravity};
  float dist;
  float collision_dist = ball_radius;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (!completed) {
      if (IsKeyDown(KEY_RIGHT))
        pad_position.x += arrow_shift[0];
      if (IsKeyDown(KEY_LEFT))
        pad_position.x -= arrow_shift[0];
      if (IsKeyDown(KEY_UP))
        pad_position.y -= arrow_shift[1];
      if (IsKeyDown(KEY_DOWN))
        pad_position.y += arrow_shift[1];

      if (pad_position.y >= HEIGHT - brick_dims[1]) {
        pad_position.y = HEIGHT - brick_dims[1];
      }
      if (pad_position.y <= HEIGHT * brick_factor) {
        pad_position.y = HEIGHT * brick_factor;
      }
      if (pad_position.x >= (WIDTH - pad_dims_x)) {
        pad_position.x = (WIDTH - pad_dims_x);
      }
      if (pad_position.x <= 0.0f) {
        pad_position.x = 0.0f;
      }

      float dt = GetFrameTime();

      ball_pos.x += ball_velocity.x * dt;
      ball_pos.y += ball_velocity.y * dt;

      dist = pad_position.y - pad_dims_y - ball_pos.y;

      if ((ball_pos.x >= pad_position.x) &&
          (ball_pos.x <= pad_position.x + pad_dims_x)) {
        if (dist <= collision_dist) {
          ball_velocity.y *= -1.0f;
          if (init) {
            init = false;
            ball_velocity.x = 30.0f;
          }
        }
      }
      if (ball_pos.y < (ball_radius + top_padding[1])) {
        ball_pos.y = ball_radius + top_padding[1];
        ball_velocity.y *= -1.0f;
      }
      if (ball_pos.x <= ball_radius) {
        ball_pos.x = ball_radius;
        ball_velocity.x *= -1.0f;
      }
      if (ball_pos.x >= WIDTH - ball_radius) {
        ball_pos.x = WIDTH - ball_radius;
        ball_velocity.x *= -1.0f;
      }

      if (ball_pos.y >= HEIGHT) {
        lost = true;
      }

      check_collisions(ball_pos, ball_velocity);
      check_completion(completed);
      DrawCircleV(ball_pos, ball_radius, WHITE);

      DrawRectangleV(pad_position, pad_dims, RED);
      for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j) {
          this->bricks[i][j].draw_brick();
        }
    }

    if (completed && !lost) {
      ClearBackground(BLACK);
      DrawText("YOU WIN!", WIDTH * 0.325, HEIGHT / 2.0, 40, GRAY);
    }

    if (lost) {
      ClearBackground(BLACK);
      DrawText("YOU LOSE!", WIDTH * 0.325, HEIGHT / 2.0, 40, GRAY);
    }

    EndDrawing();
  }
}

void Breakout::close() { CloseWindow(); }
