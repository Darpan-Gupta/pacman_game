#include<SDL.h>
#include "splash_screen.h"
#include "map.h"
#include "stats.h"
#include "pacman.h"
#include "blinky.h"
#include "sounds.h"
using namespace std;



int main(int argc, char* argv[])
{
    

    // sdl init for initializing sdl subsystems
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

    // create a window and renderer
    // (in a project we can use only one renderer)  **imp
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;


    // initialize the window
    window = SDL_CreateWindow(
        "PACMAN",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        x_window,
        y_window,
        SDL_WINDOW_SHOWN
    );


    // initialize the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);



    load_audio();

    class_map object_map(renderer);
    class_pacman object_pacman(renderer);
    class_blinky object_blinky(renderer);


    // Game Start

    while (continue_playing) {
        // clear the renderer
        SDL_RenderClear(renderer);
        render_start_page(renderer);


        // asking user to enter the game,
        while (!game_is_running) {

            // it captures all the input events happening on pc and put them in queue to perform actions on them
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    Mix_Quit();
                    SDL_Quit();
                    return 0;
                }
                else if (event.type == SDL_KEYDOWN) game_is_running = true;
            }
            SDL_Delay(100);
        }


        


        play_theme_music();
        
        // main game loop
        while (game_is_running)
        {
            SDL_Event event;

            SDL_RenderClear(renderer);

            object_map.create_map(map, renderer);
            object_pacman.render_pacman(map, renderer, &event);
            object_blinky.render_blinky(map, renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(60);

        }

        


        render_score(renderer);
        game_is_running = true;

        // asking user if he wants to continue game
        while (game_is_running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    Mix_Quit();
                    SDL_Quit();
                    return 0;
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
    object_map.~class_map();
    object_blinky.~class_blinky();
    object_pacman.~class_pacman();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();



    return 0;
}