#pragma once

#include "SDL.h"
#include <list>

#define GRID 50;

using namespace std;

class Stage1
{
public:
	Stage1();
	~Stage1();

	void HandleEvents();
	void Update();
	void Render();
	void Move();
	void AddSnake();
	bool GetItem();
	void MakeItem();
	bool Overlap();

private:

	// snake class
	class Snake {
	public:
		Snake() {
			snake_rect.x = 200;
			snake_rect.y = 200;
			snake_rect.w = GRID;
			snake_rect.h = GRID;
		}
		Snake(int x_, int y_) {
			snake_rect.x = x_;
			snake_rect.y = y_;
			snake_rect.w = GRID;
			snake_rect.h = GRID;
		}

		SDL_Rect snake_rect;
		
	};


	list<Snake> snakeList;
	
	// BG
	SDL_Rect g_bg_source_rect;
	SDL_Rect g_bg_destination_rect;
	SDL_Texture* g_bg_texture;

	// snake
	SDL_Rect g_snake_source_rect;
	SDL_Rect g_snake_destination_rect;
	SDL_Texture* g_snake_texture;

	// item
	SDL_Rect g_item_source_rect;
	SDL_Rect g_item_destination_rect;
	SDL_Texture* g_item_texture;

	// game_over
	SDL_Rect g_gameOver_rect;
	SDL_Rect g_gameOver_destination_rect;
	SDL_Texture* g_gameOver_texture;
	SDL_Surface* g_gameOver_surface;
	TTF_Font* font1;
	SDL_Color black = { 0,0,0,0 };

	// score
	SDL_Rect g_score_rect;
	SDL_Rect g_score_destination_rect;
	SDL_Texture* g_score_texture;
	SDL_Surface* g_score_surface;
	SDL_Color black_100 = { 0,0,0,100 };
	TTF_Font* font2;
	const char* g_score_char;
	char g_score_array[5];

	int g_elapsed_time_ms;

	int snake_state;		// 0 : stop
							// 1 : left
							// 2 : right
							// 3 : up
							// 4 : down

	bool game_over;

	int score;
	
	
};


