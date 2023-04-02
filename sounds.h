#pragma once

//#include<SDL.h>
#include<SDL_mixer.h>
#include"stats.h"


// variables used

Mix_Music* theme_music = NULL;
Mix_Chunk* coins_sound = NULL;
Mix_Chunk* death_sound = NULL;
//Mix_Chunk* player_caught_sound = NULL;
Mix_Music* end_scene_music = NULL;


// functions used

void load_audio();
void play_theme_music();
void play_coins_sound();
void play_death_sound();

// important:
// music and sound are different, music is the major song that you have to play in background, sound are the chunks of music (i.e. small music) that is played at special or unique events and hence their functions are also different, and also fucntion for wav and other audio formats files are different


// loading audio to variables 
// ***important, we have to free the resouces after the game is being played, for that we can simply use MIX_QUIT() to free all mix chunks and music, and its being used in main.cpp
void load_audio() {
   
    // returns 0 on failure.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    };

    theme_music = Mix_LoadMUS("./pacman_resources/Subway_Surfers_Theme_Sound_Effect.mp3");
    if (theme_music == NULL)
    {
        printf("Failed to load theme_music! SDL_mixer Error: %s\n", Mix_GetError());
    };

    coins_sound = Mix_LoadWAV("./pacman_resources/coins_sound.wav");
    if (coins_sound == NULL)
    {
        printf("Failed to load coins_sound! SDL_mixer Error: %s\n", Mix_GetError());
    };

    death_sound = Mix_LoadWAV("./pacman_resources/death_sound.wav");
    if (death_sound == NULL)
    {
        printf("Failed to load death_sound! SDL_mixer Error: %s\n", Mix_GetError());
    };

    /*player_caught_sound = Mix_LoadWAV("./pacman_resources/player_caught_sound.wav");
    if (player_caught_sound == NULL)
    {
        printf("Failed to load theme_sound! SDL_mixer Error: %s\n", Mix_GetError());
    };*/

    end_scene_music = Mix_LoadMUS("./pacman_resources/Kabuki_Yoooo_Sound.mp3");
    if (end_scene_music == NULL)
    {
        printf("Failed to load end_scene_music! SDL_mixer Error: %s\n", Mix_GetError());
    };
}


void play_theme_music() {

    // returns 0 on success, or -1 on errors

    // second parameter is for number of loops -1 for infinite times and 0 for playing once
    if (game_is_running && Mix_PlayMusic(theme_music, -1) != 0) {
        printf("theme_music can't be played, SDL_mixer Error: %s\n", Mix_GetError());
    };

}

void play_coins_sound() {
    if (Mix_PlayChannel(-1, coins_sound, 0) < 0) {
        printf("coins_sound can't be played, SDL_mixer Error: %s\n", Mix_GetError());
    };
}

void play_death_sound() {

    // stoping the theme_music and any other sound;
    Mix_HaltMusic();

    if (Mix_PlayChannel(-1, death_sound, 0) < 0) {
        printf("death_sound can't be played, SDL_mixer Error: %s\n", Mix_GetError());
    };
    /*if (Mix_PlayChannel(-1, player_caught_sound, 0) < 0) {
        printf("player_caught_sound can't be played, SDL_mixer Error: %s\n", Mix_GetError());
    };*/
    if (Mix_PlayMusic(end_scene_music, 0) < 0) {
        printf("end_scene_music can't be played, SDL_mixer Error: %s\n", Mix_GetError());
    }
}



