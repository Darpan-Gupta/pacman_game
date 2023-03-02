#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include "map.h"
#include "stats.h"
#include "pacman.h"
#include "blinky.h"
using namespace std;


int main(int argc, char* argv[])
{

    // block size will be of 50 x 48
    // wall_block size will be of 35 x 33
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

    // sdl initialization command for specifing input output devices
    SDL_Init(SDL_INIT_EVERYTHING);

    // create a window and renderer
    // (in a project we can use only one renderer)
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;


    // initialize the window
    window = SDL_CreateWindow(
        "desi pacman",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        x_window,
        y_window,
        SDL_WINDOW_SHOWN
    );


    // initialize the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);


    // making object of class: game_map, code in map.h header file
    class_map object_map(renderer);

    // making object of class_pacman, code in pacman.h header file
    class_pacman object_pacman(renderer);

    class_blinky object_blinky(renderer);


    // main game loop
    while (game_is_running)
    {
        // it captures all the input events happening on pc and put them in queue to perform actions on them
        SDL_Event event;

       /* while (SDL_PollEvent(&event)) {
            cout << "check2\n";
            if (event.type == SDL_QUIT) {
                game_is_running = false;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                cout << "mouse is moving";
            }
        }*/

        // clear the renderer
        SDL_RenderClear(renderer);

        object_map.create_map(map, renderer);
        object_pacman.render_pacman(map, renderer, &event);
        object_blinky.render_blinky(map, renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(60);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}