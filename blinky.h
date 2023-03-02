#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<vector>
#include<queue>
#include "stats.h"
#include<iostream>
using namespace std;

class class_blinky
{
public:
	// constructor to initialize red_blinky and blinky images to source rectangle
	class_blinky(SDL_Renderer* renderer);

	void path_finder(string* map);
	void render_blinky(string* map, SDL_Renderer* renderer);

private:
	SDL_Texture* red_blinky = nullptr;

	SDL_Rect up[2];
	SDL_Rect down[2];
	SDL_Rect left[2];
	SDL_Rect right[2];
	SDL_Rect blinky_position;

	SDL_Rect blinky_shape_select;
	bool fluctuater = true;

	int counter_to_slow = 0;
};



class_blinky::class_blinky(SDL_Renderer* renderer) {

	red_blinky = IMG_LoadTexture(renderer, "./pacman_resources/Blinky.bmp");

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

	blinky_position.h = y_block;
	blinky_position.w = x_block;

	blinky_position.x = x_block * current_x_blinky;
	blinky_position.y = y_block * current_y_blinky;

	SDL_RenderCopy(renderer, red_blinky, &left[1], &blinky_position);
	blinky_shape_select = left[1];
}

struct struct_coordinates {
	int x, y;
}temp;



void class_blinky::path_finder(string* map) {
	
	if (current_x_pacman == current_x_blinky && current_y_pacman == current_y_blinky) return;
	
	queue<struct_coordinates> buffer_queue;

	while (!buffer_queue.empty()) buffer_queue.pop();

		
	temp.x = current_x_pacman;
	temp.y = current_y_pacman;
	buffer_queue.push(temp);



	/*while (!buffer_queue.empty()) {
		
		if (map[buffer_queue.front().x - 1][buffer_queue.front().y] != '#') {
			temp.x = buffer_queue.front().x - 1;
			temp.y = buffer_queue.front().y;
			buffer_queue.push(temp);


			vector<struct_coordinates> vector_curr_prev;
			vector_curr_prev.push_back(temp);
			vector_curr_prev.push_back(buffer_queue.front());
			vector_bfs_curr_and_prev_nodes.push_back(vector_curr_prev);

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;
				current_y_blinky = buffer_queue.front().y;
				break;
			}

			buffer_queue.pop();
		}

		if (map[buffer_queue.front().x ][buffer_queue.front().y - 1] != '#') {
			temp.x = buffer_queue.front().x;
			temp.y = buffer_queue.front().y - 1;
			buffer_queue.push(temp);


			vector<struct_coordinates> vector_curr_prev;
			vector_curr_prev.push_back(temp);
			vector_curr_prev.push_back(buffer_queue.front());
			vector_bfs_curr_and_prev_nodes.push_back(vector_curr_prev);

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;
				current_y_blinky = buffer_queue.front().y;
				break;
			}

			buffer_queue.pop();
		}

		if (map[buffer_queue.front().x + 1][buffer_queue.front().y] != '#') {
			temp.x = buffer_queue.front().x + 1;
			temp.y = buffer_queue.front().y;
			buffer_queue.push(temp);


			vector<struct_coordinates> vector_curr_prev;
			vector_curr_prev.push_back(temp);
			vector_curr_prev.push_back(buffer_queue.front());
			vector_bfs_curr_and_prev_nodes.push_back(vector_curr_prev);

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;
				current_y_blinky = buffer_queue.front().y;
				break;
			}

			buffer_queue.pop();
		}

		if (map[buffer_queue.front().x][buffer_queue.front().y + 1] != '#') {
			temp.x = buffer_queue.front().x;
			temp.y = buffer_queue.front().y + 1;
			buffer_queue.push(temp);


			vector<struct_coordinates> vector_curr_prev;
			vector_curr_prev.push_back(temp);
			vector_curr_prev.push_back(buffer_queue.front());
			vector_bfs_curr_and_prev_nodes.push_back(vector_curr_prev);

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;
				current_y_blinky = buffer_queue.front().y;
				break;
			}

			buffer_queue.pop();

		}

	}*/

	bool blocks_visited[blocks_in_y][blocks_in_x] = {false};

	while (!buffer_queue.empty()) {


		blocks_visited[buffer_queue.front().y][buffer_queue.front().x] = true;
		
		if ( blocks_visited[buffer_queue.front().y][buffer_queue.front().x - 1] == false && map[buffer_queue.front().y][buffer_queue.front().x - 1] != '#') {
			temp.x = buffer_queue.front().x - 1;
			temp.y = buffer_queue.front().y;
			buffer_queue.push(temp);

			//cout << "1.1\n";

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;

				if (fluctuater) blinky_shape_select = right[0];
				else blinky_shape_select = right[1];

				//cout << "1.2\n";

				break;
			}

			
		}

		if (blocks_visited[buffer_queue.front().y - 1][buffer_queue.front().x] == false && map[buffer_queue.front().y - 1][buffer_queue.front().x] != '#') {
			temp.x = buffer_queue.front().x;
			temp.y = buffer_queue.front().y - 1;
			buffer_queue.push(temp);

			//cout << "2.1\n";

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_y_blinky = buffer_queue.front().y;

				if (fluctuater) blinky_shape_select = down[0];
				else blinky_shape_select = down[1];

				//cout << "2.2\n";

				break;
			}
		}

		if (blocks_visited[buffer_queue.front().y][buffer_queue.front().x + 1] == false && map[buffer_queue.front().y][buffer_queue.front().x + 1] != '#') {
			temp.x = buffer_queue.front().x + 1;
			temp.y = buffer_queue.front().y;
			buffer_queue.push(temp);

			//cout << "3.1\n";

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_x_blinky = buffer_queue.front().x;

				if (fluctuater) blinky_shape_select = left[0];
				else blinky_shape_select = left[1];

				//cout << "3.2\n";

				break;
			}
		}

		if (blocks_visited[buffer_queue.front().y + 1][buffer_queue.front().x] == false && map[buffer_queue.front().y + 1][buffer_queue.front().x] != '#') {
			temp.x = buffer_queue.front().x;
			temp.y = buffer_queue.front().y + 1;
			buffer_queue.push(temp);

			//cout << "4.1\n";

			if (temp.x == current_x_blinky && temp.y == current_y_blinky) {
				current_y_blinky = buffer_queue.front().y;

				if (fluctuater) blinky_shape_select = up[0];
				else blinky_shape_select = up[1];

				//cout << "4.2\n";

				break;
			}
		}

		buffer_queue.pop();
	}
	fluctuater = !fluctuater;
	//cout << "check\n";


	/*int x = vector_bfs_curr_and_prev_nodes.end()[1][0];
	int y = vector_bfs_curr_and_prev_nodes.end()[1][1];

	for (auto iter = vector_bfs_curr_and_prev_nodes.end(); ; iter--) {

		if (x == iter[0][0] and y == iter[0][1]) {
			current_x_blinky = iter[1][0];
			current_y_blinky = iter[1][1];
			break;
		}

	}*/

}

void class_blinky::render_blinky(string* map, SDL_Renderer* renderer) {

	//SDL_Delay(100000);
	counter_to_slow++;
	//cout << counter_to_slow << endl;
	if (counter_to_slow == 4) {
		path_finder(map);
		//cout << "check\n";
		counter_to_slow = 0;
	}
		
	blinky_position.x = x_block * current_x_blinky;
	blinky_position.y = y_block * current_y_blinky;
	SDL_RenderCopy(renderer, red_blinky, &blinky_shape_select, &blinky_position);
	
}