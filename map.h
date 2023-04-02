#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include "stats.h"

// map is accessed, first in y axis then in x axis like (y,x)

class class_map
{
public:
	// constructer for initializing wall_texture, point_texture and destination rectangle parameters
	class_map(SDL_Renderer* renderer);
	~class_map() {
		SDL_DestroyTexture(wall_texture);
		SDL_DestroyTexture(point_texture);
	};

	// function to render map on renderer
	void create_map(std::string* map, SDL_Renderer* renderer);

private:
	SDL_Texture* wall_texture = nullptr;
	SDL_Texture* point_texture = nullptr;
	SDL_Rect dstrect;
};


class_map::class_map(SDL_Renderer* renderer) {
	wall_texture = IMG_LoadTexture(renderer, "./pacman_resources/wall.bmp");
	point_texture = IMG_LoadTexture(renderer, "./pacman_resources/ball.png");

	dstrect.x = 0; //  initial x coordinate
	dstrect.y = 0; //  initial y coordinate
	dstrect.w = x_wall_block; // width of rectangle
	dstrect.h = y_wall_block; // height of rectangle
};



void class_map::create_map(std::string* map, SDL_Renderer* renderer) {

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
		dstrect.x = 0;
		dstrect.y += y_block;

	}

	dstrect.x = 0;
	dstrect.y = 0;
}

