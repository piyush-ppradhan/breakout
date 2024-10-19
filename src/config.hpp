#pragma once
constexpr int WIDTH = 640;
constexpr int HEIGHT = 800;
constexpr float pad_dims_x = 150.0f;
constexpr float pad_dims_y = 15.0f;
constexpr float top_padding[] = {30.0f, 40.0f};
constexpr int nrows = 4;
constexpr int ncols = 5;
constexpr float brick_factor = 0.4f; // bricks can cover upto 60% of height;
constexpr float brick_space = 10.0f;
constexpr float brick_dims[] = {
    (WIDTH - 2 * top_padding[0] - nrows * brick_space) / nrows,
    (brick_factor * HEIGHT - top_padding[1] - ncols * brick_space) / ncols};
constexpr float arrow_shift[] = {2.0f, 2.0f};
constexpr float ball_radius = 8.0f;
constexpr float gravity = 250.0f;
constexpr float init_ball_pos[] = {WIDTH / 2.0f, HEIGHT / 2.0f};
