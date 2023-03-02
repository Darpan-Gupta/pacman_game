#pragma once

#define x_window 800
#define y_window 432

#define x_block 50
#define y_block 48

#define blocks_in_x 16
#define blocks_in_y 9

#define x_wall_block 35
#define y_wall_block 33

int score = 0;

int current_x_pacman = 1;
int current_y_pacman = 1;

int current_x_blinky = 14;
int current_y_blinky = 7;

bool game_is_running = true;