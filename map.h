#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include "stats.h"
using namespace std;


class class_map
{
public:
	// constructer for initializing wall_texture, point_texture and destination rectangle parameters
	class_map(SDL_Renderer* renderer);

	// function to render map on renderer
	void create_map(string* map, SDL_Renderer* renderer);

private:
	SDL_Texture* wall_texture = nullptr;
	SDL_Texture* point_texture = nullptr;
	SDL_Rect dstrect;
};


class_map::class_map(SDL_Renderer* renderer) {
	wall_texture = IMG_LoadTexture(renderer, "./pacman_resources/wall.bmp");
	point_texture = IMG_LoadTexture(renderer, "./pacman_resources/point.bmp");

	dstrect.x = 7; //  initial x coordinate
	dstrect.y = 7; //  initial y coordinate
	dstrect.w = x_wall_block; // width of rectangle
	dstrect.h = y_wall_block; // height of rectangle
};



void class_map::create_map(string* map, SDL_Renderer* renderer) {

	for (int i = 0; i < blocks_in_y; i++)
	{

		for (int j = 0; j < blocks_in_x; j++)
		{

			if (map[i][j] == '#')
			{
				SDL_RenderCopy(renderer, wall_texture, NULL, &dstrect);
			}
			else if (map[i][j] == '.')
			{
				SDL_RenderCopy(renderer, point_texture, NULL, &dstrect);
			}

			dstrect.x += x_block;
		}
		dstrect.x = 7;
		dstrect.y += y_block;

	}

	dstrect.x = 7;
	dstrect.y = 7;
}

