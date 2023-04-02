#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include "stats.h"
#include "sounds.h"

class class_pacman
{
public:
	// constructor to initalize pacman_texture, pacman images to source rectangles, inital position and inital pacman shape
	class_pacman(SDL_Renderer* renderer);
	~class_pacman() { SDL_DestroyTexture(pacman_texture); };

	// function to change the position and shape of pacman if any key is pressed and to maintain the position if any key is not pressed
	void render_pacman(std::string* map, SDL_Renderer* renderer, SDL_Event* event);

private:

	SDL_Texture* pacman_texture = nullptr;

	SDL_Rect up[2];
	SDL_Rect down[2];
	SDL_Rect left[2];
	SDL_Rect right[2];
	SDL_Rect pacman_circle;
	SDL_Rect pacman_shape_select;
	SDL_Rect pacman_position;

	char current_direction_of_pacman = 0;
	char next_direction_of_pacman = 0;

	// to fluctuate between the two images of pacman in one direction, will be used to provide a illusion of movement
	bool fluctuater = true;
	// variable to slow the speed of pacman
	int counter_to_slow = 0;
	int key_case_selection = 0;

};


class_pacman::class_pacman(SDL_Renderer* renderer) {

	pacman_texture = IMG_LoadTexture(renderer, "./pacman_resources/PacMan.bmp");

	up[0].x = 50;
	up[0].y = 25;
	up[0].w = 25;
	up[0].h = 25;

	up[1].x = 75;
	up[1].y = 25;
	up[1].w = 25;
	up[1].h = 25;


	down[0].x = 50;
	down[0].y = 0;
	down[0].w = 25;
	down[0].h = 25;

	down[1].x = 75;
	down[1].y = 0;
	down[1].w = 25;
	down[1].h = 25;


	left[0].x = 0;
	left[0].y = 0;
	left[0].w = 25;
	left[0].h = 25;

	left[1].x = 25;
	left[1].y = 0;
	left[1].w = 25;
	left[1].h = 25;


	right[0].x = 0;
	right[0].y = 25;
	right[0].w = 25;
	right[0].h = 25;

	right[1].x = 25;
	right[1].y = 25;
	right[1].w = 25;
	right[1].h = 25;

	pacman_circle.x = 0;
	pacman_circle.y = 50;
	pacman_circle.h = 25;
	pacman_circle.w = 25;

	pacman_position.h = y_block;
	pacman_position.w = x_block;

	pacman_position.x = x_block * current_x_pacman;
	pacman_position.y = y_block * current_y_pacman;

	SDL_RenderCopy(renderer, pacman_texture, &pacman_circle, &pacman_position);
	pacman_shape_select = pacman_circle;

	

}


void class_pacman::render_pacman(std::string* map, SDL_Renderer* renderer, SDL_Event* event) {

	/*  // this code is for manual speed of pacman.
	
	while (SDL_PollEvent(event)) {

		if (event->type == SDL_QUIT) game_is_running = false;

		else if (event->type == SDL_KEYDOWN) {

			switch (event->key.keysym.sym)
			{
			case SDLK_UP:
				if (map[current_y_pacman - 1][current_x_pacman] != '#') {
					current_y_pacman--;

					if (fluctuater) pacman_shape_select = up[0];

					else pacman_shape_select = up[1];

				}
				break;
			case SDLK_DOWN:
				if (map[current_y_pacman + 1][current_x_pacman] != '#') {
					current_y_pacman++;

					if (fluctuater) pacman_shape_select = down[0];

					else pacman_shape_select = down[1];
				}
				break;
			case SDLK_LEFT:
				if (map[current_y_pacman][current_x_pacman - 1] != '#') {
					current_x_pacman--;

					if (fluctuater) pacman_shape_select = left[0];

					else pacman_shape_select = left[1];
				}
				break;
			case SDLK_RIGHT:
				if (map[current_y_pacman][current_x_pacman + 1] != '#') {
					current_x_pacman++;

					if (fluctuater) pacman_shape_select = right[0];

					else pacman_shape_select = right[1];
				}
				break;
			default:
				break;
			}
			fluctuater = !fluctuater;

		}



		if (map[current_y_pacman][current_x_pacman] == '.') {
			map[current_y_pacman][current_x_pacman] = ' ';
			score += 10;
		}

		pacman_position.x = x_block * current_x_pacman;
		pacman_position.y = y_block * current_y_pacman;

		// here two sdl_rendercopy (one now and one after while loop) are used because
		// this one:
		// to render any change in pacman position if any key is pressed
		SDL_RenderCopy(renderer, pacman_texture, &pacman_shape_select, &pacman_position);

	}

	*/
	


	while (SDL_PollEvent(event)) {

		if (event->type == SDL_QUIT) game_is_running = false;

		else if (event->type == SDL_KEYDOWN) {

			if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_w) key_case_selection = 1;
			else if (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s) key_case_selection = 2;
			else if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_a) key_case_selection = 3;
			else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d) key_case_selection = 4;
			else key_case_selection = 0;
			 

			

		}

	}

	switch (key_case_selection)
	{
	case 1:
		next_direction_of_pacman = 'u';
		break;

	case 2:
		next_direction_of_pacman = 'd';
		break;

	case 3:
		next_direction_of_pacman = 'l';
		break;

	case 4:
		next_direction_of_pacman = 'r';
		break;

	default:
		break;
	}

	counter_to_slow++;

	if (counter_to_slow == 3) {

		if (next_direction_of_pacman == 'u' && map[current_y_pacman - 1][current_x_pacman] != '#') current_direction_of_pacman = next_direction_of_pacman;

		else if (next_direction_of_pacman == 'd' && map[current_y_pacman + 1][current_x_pacman] != '#') current_direction_of_pacman = next_direction_of_pacman;

		else if (next_direction_of_pacman == 'l' && map[current_y_pacman][current_x_pacman - 1] != '#') current_direction_of_pacman = next_direction_of_pacman;

		else if (next_direction_of_pacman == 'r' && map[current_y_pacman][current_x_pacman + 1] != '#') current_direction_of_pacman = next_direction_of_pacman;



		if (current_direction_of_pacman == 'u' && map[current_y_pacman - 1][current_x_pacman] != '#') {
			current_y_pacman--;
			if (fluctuater) pacman_shape_select = up[0];
			else pacman_shape_select = up[1];
		}

		else if (current_direction_of_pacman == 'd' && map[current_y_pacman + 1][current_x_pacman] != '#') {
			current_y_pacman++;
			if (fluctuater) pacman_shape_select = down[0];
			else pacman_shape_select = down[1];
		}

		else if (current_direction_of_pacman == 'l' && map[current_y_pacman][current_x_pacman - 1] != '#') {
			current_x_pacman--;
			if (fluctuater) pacman_shape_select = left[0];
			else pacman_shape_select = left[1];
		}

		else if (current_direction_of_pacman == 'r' && map[current_y_pacman][current_x_pacman + 1] != '#') {
			current_x_pacman++;
			if (fluctuater) pacman_shape_select = right[0];
			else pacman_shape_select = right[1];
		}


		if (map[current_y_pacman][current_x_pacman] == '.') {
			map[current_y_pacman][current_x_pacman] = ' ';
			score += 10;
			play_coins_sound();
		}
		if (score == max_score) {
			game_is_running = false;
			play_death_sound();
		}

		pacman_position.x = x_block * current_x_pacman;
		pacman_position.y = y_block * current_y_pacman;
		fluctuater = !fluctuater;
		

		// here two sdl_rendercopy (one now and one after while loop) are used because
		// this one:
		// to render any change in pacman position if any key is pressed
		SDL_RenderCopy(renderer, pacman_texture, &pacman_shape_select, &pacman_position);

		counter_to_slow = 0;
	}
	// and this one:
	// to maintain the position of pacman if no key is pressed
	SDL_RenderCopy(renderer, pacman_texture, &pacman_shape_select, &pacman_position);

}
