#pragma once
#include<string>
using namespace std;

#define x_window 800
#define y_window 432

#define x_block 50
#define y_block 48

#define blocks_in_x 16
#define blocks_in_y 9

#define x_wall_block 35
#define y_wall_block 33

const string initial_map[blocks_in_y]
{
    "################",
    "#....#....#....#",
    "#.##.#.##.#.##.#",
    "#.#..........#.#",
    "#...#..##..#...#",
    "#.#..........#.#",
    "#.##.#.##.#.##.#",
    "#....#....#....#",
    "################"
};

const int initial_score = 0;

const int initial_x_pacman = 1;
const int initial_y_pacman = 1;

const int initial_x_blinky = 14;
const int initial_y_blinky = 7;

string map[blocks_in_y]
{
    "################",
    "#....#....#....#",
    "#.##.#.##.#.##.#",
    "#.#..........#.#",
    "#...#..##..#...#",
    "#.#..........#.#",
    "#.##.#.##.#.##.#",
    "#....#....#....#",
    "################"
};

int score = 0;

int current_x_pacman = 1;
int current_y_pacman = 1;

int current_x_blinky = 14;
int current_y_blinky = 7;

bool game_is_running = false;
bool continue_playing = true;