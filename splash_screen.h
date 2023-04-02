#pragma once

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
#include "stats.h"

// functions used

void render_start_page(SDL_Renderer* renderer);
void render_score(SDL_Renderer* renderer);



void render_start_page(SDL_Renderer* renderer) {
	TTF_Init();
	TTF_Font* start_font = TTF_OpenFont("./pacman_resources/SHOWG.ttf", 120);

	SDL_Color pacman_heading_color = { 253,255,0 };

	SDL_Surface* text_surface = TTF_RenderText_Solid(start_font, "PACMAN", pacman_heading_color );

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);


	SDL_Rect text_dest_rect;

	text_dest_rect.h = text_surface->h;
	text_dest_rect.w = text_surface->w;
	text_dest_rect.x = x_window / 2 - text_dest_rect.w / 2;
	text_dest_rect.y = y_window / 2 - text_dest_rect.h / 2;
	
	

	SDL_RenderCopy(renderer, text_texture, NULL, &text_dest_rect);

	SDL_RenderPresent(renderer);


	SDL_Delay(800);


	// since the previous text is copied on renderer, we can use its resources for next text 

	pacman_heading_color = { 245, 245, 245 };
	start_font = TTF_OpenFont("./pacman_resources/ARLRDBD.ttf", 20);
	text_surface = TTF_RenderText_Solid(start_font, "Press any key to start the game", pacman_heading_color);
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	text_dest_rect.h = text_surface->h;
	text_dest_rect.w = text_surface->w;
	text_dest_rect.x = x_window / 2 - text_dest_rect.w / 2;
	text_dest_rect.y = 3*y_window / 4 - text_dest_rect.h / 2;
	SDL_RenderCopy(renderer, text_texture, NULL, &text_dest_rect);

	text_surface = TTF_RenderText_Solid(start_font, "or press Esc to quit", pacman_heading_color);
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	text_dest_rect.h = text_surface->h;
	text_dest_rect.w = text_surface->w;
	text_dest_rect.x = x_window / 2 - text_dest_rect.w / 2;
	text_dest_rect.y = 3 * y_window / 4 + text_dest_rect.h / 2;
	SDL_RenderCopy(renderer, text_texture, NULL, &text_dest_rect);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);
	TTF_CloseFont(start_font);
	TTF_Quit();
}


void render_score(SDL_Renderer* renderer) {
	TTF_Init();
	TTF_Font* score_font = TTF_OpenFont("pacman_resources/SHOWG.ttf", 100);
	
	SDL_Color score_color = { 245, 100, 100 };
	std::string str_score = "SCORE: ";
	str_score.append(std::to_string(score));
	SDL_Surface* score_surface = TTF_RenderText_Blended(score_font, str_score.c_str(), score_color);
	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

	SDL_Rect score_dest_rect;
	score_dest_rect.h = score_surface->h;
	score_dest_rect.w = score_surface->w;
	score_dest_rect.x = x_window/2 - score_dest_rect.w/2;
	score_dest_rect.y = y_window/2 - score_dest_rect.h/2;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, score_texture, NULL, &score_dest_rect);
	SDL_RenderPresent(renderer);

	if (score == max_score) {

		score_color = { 245, 255, 0 };
		TTF_Font* message_font = TTF_OpenFont("pacman_resources/SHOWG.ttf", 100);
		score_surface = TTF_RenderText_Solid(message_font, "You WIN !!!", score_color);
		score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

		score_dest_rect.h = score_surface->h;
		score_dest_rect.w = score_surface->w;
		score_dest_rect.x = x_window / 2 - score_dest_rect.w / 2;
		score_dest_rect.y = y_window / 4 - score_dest_rect.h / 2;


		SDL_RenderCopy(renderer, score_texture, NULL, &score_dest_rect);
	}


	// reusing resources to put delay in 2nd apperence of the text

	SDL_Delay(800);
	

	score_color = { 245, 245, 245 };
	TTF_Font* message_font = TTF_OpenFont("pacman_resources/ARLRDBD.ttf", 30);
	score_surface = TTF_RenderText_Solid(message_font, "Press any key to continue", score_color);
	score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

	score_dest_rect.h = score_surface->h;
	score_dest_rect.w = score_surface->w;
	score_dest_rect.x = x_window / 2 - score_dest_rect.w / 2;
	score_dest_rect.y = 3*y_window / 4 - score_dest_rect.h / 2;


	SDL_RenderCopy(renderer, score_texture, NULL, &score_dest_rect);
	SDL_RenderPresent(renderer);
	

	SDL_FreeSurface(score_surface);
	SDL_DestroyTexture(score_texture);
	TTF_CloseFont(score_font);
	TTF_CloseFont(message_font);
	TTF_Quit();
}