#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
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



void create_map(string *map, SDL_Renderer* renderer) {

    /*for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < blocks_in_x; j++)
        {

        cout << map[i][j];
        }
        cout << endl;
    }*/


    SDL_Texture* wall_texture = nullptr;
    SDL_Texture* point_texture = nullptr;


    wall_texture = IMG_LoadTexture(renderer, "./pacman_resources/wall.bmp");
    point_texture = IMG_LoadTexture(renderer, "./pacman_resources/point.bmp");

    SDL_Rect dstrect;
    dstrect.x = 7;
    dstrect.y = 7;
    dstrect.w = x_wall_block;
    dstrect.h = y_wall_block;     
          

    for (int i = 0; i < blocks_in_y; i++)
    {   
        
        for (int j = 0; j < blocks_in_x; j++)
        {
            

            if (map[i][j] == '#')
            {
                //SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, wall_texture, NULL, &dstrect);
            }
            else if (map[i][j] == '.')
            {
                //SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, point_texture, NULL, &dstrect);
            }
            /*else if (map[i][j] == " ")
            {
                continue;
            }*/

            dstrect.x += x_block;
        }
        dstrect.x = 7;
        dstrect.y += y_block;

    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(wall_texture);
    SDL_DestroyTexture(point_texture);
}



void pacman(string *map, SDL_Renderer *renderer, SDL_Event *event) {
    int pacman_curr_x;
    int pacman_curr_y;
}



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


    SDL_Init(SDL_INIT_EVERYTHING);
    
    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;



    window = SDL_CreateWindow(
        "desi pacman",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        x_window,
        y_window,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    //texture = SDL_CreateTexture(renderer, SDL_PixelType, SDL_TEXTUREACCESS_STATIC, 800, 450);

    create_map(map, renderer);

    bool game_is_running = true;

    while (game_is_running)
    {
        SDL_Event event;
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game_is_running = false;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                cout << "mouse is moving";
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}