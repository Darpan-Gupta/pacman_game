#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<SDL_ttf.h>
#include<conio.h>
#include "splash_screen.h"
#include "map.h"
#include "stats.h"
#include "pacman.h"
#include "blinky.h"
using namespace std;


// map is accessed, first in y axis then in x axis like (y,x)


int main(int argc, char* argv[])
{

    // block size will be of 50 x 48
    // wall_block size will be of 35 x 33
    

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





    // Game Start


    while (continue_playing) {

        SDL_RenderClear(renderer);
        render_start_page(renderer);

        while (!game_is_running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                }
                else if (event.type == SDL_KEYDOWN) game_is_running = true;
            }
            SDL_Delay(100);
        }


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

             // clear the renderer
            SDL_RenderClear(renderer);

            object_map.create_map(map, renderer);
            object_pacman.render_pacman(map, renderer, &event);
            object_blinky.render_blinky(map, renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(60);

        }

        object_map.~class_map();
        object_blinky.~class_blinky();
        object_pacman.~class_pacman();


        render_score(renderer);
        game_is_running = true;
        while (game_is_running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    game_is_running = false;
                    continue_playing = false;
                }
                else if (event.type == SDL_KEYDOWN) {
                    for (int i = 0; i < blocks_in_y; i++) {
                        map[i] = initial_map[i];
                    }
                    score = initial_score;
                    current_x_blinky = initial_x_blinky;
                    current_y_blinky = initial_y_blinky;
                    current_x_pacman = initial_x_pacman;
                    current_y_pacman = initial_y_pacman;
                    game_is_running = false;
                }
            }
            SDL_Delay(100);
        }

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}