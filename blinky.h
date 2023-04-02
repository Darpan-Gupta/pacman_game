 #pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<queue>
#include "stats.h"
using namespace std;

class class_blinky
{
public:
	// constructor to initialize red_blinky and blinky images to source rectangle
	class_blinky(SDL_Renderer* renderer);
	~class_blinky() { SDL_DestroyTexture(red_blinky); };

	void path_finder(std::string* map);
	void render_blinky(std::string* map, SDL_Renderer* renderer);

private:
	SDL_Texture* red_blinky = nullptr;

	SDL_Rect up[2];
	SDL_Rect down[2];
	SDL_Rect left[2];
	SDL_Rect right[2];
	SDL_Rect blinky_position;

	SDL_Rect blinky_shape_select;
	
	// to fluctuate between the two images of blinky in one direction, will be used to provide a illusion of movement
	bool fluctuater = true;

	// variable to slow the speed of blinky
	int counter_to_slow = 0;
};



class_blinky::class_blinky(SDL_Renderer* renderer) {

	// loading texture
	red_blinky = IMG_LoadTexture(renderer, "./pacman_resources/Blinky.bmp");


	// assigning sdl_rect values to access different blinky positions
	up[0].x = 0;
	up[0].y = 0;
	up[0].w = 25;
	up[0].h = 25;

	up[1].x = 25;
	up[1].y = 0;
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


	left[0].x = 50;
	left[0].y = 25;
	left[0].w = 25;
	left[0].h = 25;

	left[1].x = 75;
	left[1].y = 25;
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


	// assigning height and width parameter of blinky
	blinky_position.h = y_block;
	blinky_position.w = x_block;

	// assigning initial blinky position
	blinky_position.x = x_block * current_x_blinky;
	blinky_position.y = y_block * current_y_blinky;

	SDL_RenderCopy(renderer, red_blinky, &left[1], &blinky_position);
	blinky_shape_select = left[1];
}

struct struct_coordinates {
	int x, y;
}temp;


// finding shortest path form pacman to blinky using the concept of breadth first search(bfs)
void class_blinky::path_finder(std::string* map) {
	
	if (current_x_pacman == current_x_blinky && current_y_pacman == current_y_blinky) return;
	
	queue<struct_coordinates> buffer_queue;




	// working of bfs:
	// first we push the current value of pacman to queue, than from that block check its surrounding blocks(up, down, leftl right) if they are not the wall(or '#' here) than pushback that block to the queue;
	// than pop the queue, and repeat the step 1&2 until the queue is empty or until we find the blinky, if we find the blinky than we make the blinky's current position to the previous block that found it;
	// this way, for every game loop blinky retrace the shortest posible path to pacman, and just move 1 block and repeat this process until pacman is found;




	// making sure the queue is empty
	while (!buffer_queue.empty()) buffer_queue.pop();
	
	// pushing the current position of pacman in queue from where the bfs will start
	temp.x = current_x_pacman;
	temp.y = current_y_pacman;
	buffer_queue.push(temp);
	
	// creating a temporary box like structure of 2d boolean array so that we can keep tack of vistied blocks of the box, so that we may not put a visited block back to the queue;
	bool blocks_visited[blocks_in_y][blocks_in_x] = {false};

	while (!buffer_queue.empty()) {

		// marking that the block is being visited
		blocks_visited[buffer_queue.front().y][buffer_queue.front().x] = true;
		
		// checking if the block is visited or not, if not than checking if its not a wall, if not pushback it to queue
		if ( blocks_visited[buffer_queue.front().y][buffer_queue.front().x - 1] == false && map[buffer_queue.front().y][buffer_queue.front().x - 1] != '#') {
			temp.x = buffer_queue.front().x - 1;
			temp.y = buffer_queue.front().y;
			buffer_queue.push(temp);

			// checking if blinky is found, if yes than changing its position to previous block position
			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;

				if (fluctuater) blinky_shape_select = right[0];
				else blinky_shape_select = right[1];


				break;
			}			
		}

		if (blocks_visited[buffer_queue.front().y - 1][buffer_queue.front().x] == false && map[buffer_queue.front().y - 1][buffer_queue.front().x] != '#') {
			temp.x = buffer_queue.front().x;
			temp.y = buffer_queue.front().y - 1;
			buffer_queue.push(temp);


			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_y_blinky = buffer_queue.front().y;

				if (fluctuater) blinky_shape_select = down[0];
				else blinky_shape_select = down[1];


				break;
			}
		}

		if (blocks_visited[buffer_queue.front().y][buffer_queue.front().x + 1] == false && map[buffer_queue.front().y][buffer_queue.front().x + 1] != '#') {
			temp.x = buffer_queue.front().x + 1;
			temp.y = buffer_queue.front().y;
			buffer_queue.push(temp);


			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;

				if (fluctuater) blinky_shape_select = left[0];
				else blinky_shape_select = left[1];


				break;
			}
		}

		if (blocks_visited[buffer_queue.front().y + 1][buffer_queue.front().x] == false && map[buffer_queue.front().y + 1][buffer_queue.front().x] != '#') {
			temp.x = buffer_queue.front().x;
			temp.y = buffer_queue.front().y + 1;
			buffer_queue.push(temp);


			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_y_blinky = buffer_queue.front().y;

				if (fluctuater) blinky_shape_select = up[0];
				else blinky_shape_select = up[1];


				break;
			}
		}

		buffer_queue.pop();
	}
	fluctuater = !fluctuater;


}

// to render the final position and shape of blinky on renderer
void class_blinky::render_blinky(std::string* map, SDL_Renderer* renderer) {


	// code to slow the speed of blinky
	counter_to_slow++;
	if (counter_to_slow == 4) {
		path_finder(map);
		counter_to_slow = 0;
	}
		
	blinky_position.x = x_block * current_x_blinky;
	blinky_position.y = y_block * current_y_blinky;

	if (current_x_blinky == current_x_pacman && current_y_blinky == current_y_pacman) {
		game_is_running = false;
		play_death_sound();
		SDL_Delay(500);
	} 

	SDL_RenderCopy(renderer, red_blinky, &blinky_shape_select, &blinky_position);
	
}