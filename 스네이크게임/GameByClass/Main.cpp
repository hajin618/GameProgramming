#include "GameClass.h"
#include "Main.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Stage1::Stage1()
{
	g_elapsed_time_ms = 0;
	snake_state = 0;
	snakeList.push_front(Snake());
	game_over = false;

	score = 0;
	sprintf(g_score_array, "%d", score);
	g_score_char = g_score_array;

	// BG
	SDL_Surface* bg_surface = IMG_Load("../../Resources/main.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 860;
	g_bg_source_rect.h = 430;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 800;
	g_bg_destination_rect.h = 700;


	// snake
	SDL_Surface* snake_surface = IMG_Load("../../Resources/face.png");
	g_snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_surface);
	SDL_FreeSurface(snake_surface);

	g_snake_source_rect.x = 0;
	g_snake_source_rect.y = 0;
	g_snake_source_rect.w = 394;
	g_snake_source_rect.h = 394;

	g_snake_destination_rect.x = 200;
	g_snake_destination_rect.y = 200;
	g_snake_destination_rect.w = GRID;
	g_snake_destination_rect.h = GRID;


	// item
	SDL_Surface* item_surface = IMG_Load("../../Resources/item.jpg");
	SDL_SetColorKey(item_surface, SDL_TRUE, SDL_MapRGB(item_surface->format, 255, 255, 255));
	g_item_texture = SDL_CreateTextureFromSurface(g_renderer, item_surface);
	SDL_FreeSurface(item_surface);

	g_item_source_rect.x = 0;
	g_item_source_rect.y = 0;
	g_item_source_rect.w = 607;
	g_item_source_rect.h = 548;

	g_item_destination_rect.x = 400;
	g_item_destination_rect.y = 400;
	g_item_destination_rect.w = GRID;
	g_item_destination_rect.h = GRID;


	// game over
	font1=TTF_OpenFont("../../Resources/arose.ttf", 100);
	g_gameOver_surface = TTF_RenderText_Blended(font1, "Game Over", black);

	g_gameOver_rect.x = 0;
	g_gameOver_rect.y = 0;
	g_gameOver_rect.w = g_gameOver_surface->w;
	g_gameOver_rect.h = g_gameOver_surface->h;

	g_gameOver_destination_rect.x = 100;
	g_gameOver_destination_rect.y = 100;
	g_gameOver_destination_rect.w = g_gameOver_rect.w;
	g_gameOver_destination_rect.h = g_gameOver_rect.h;

	g_gameOver_texture= SDL_CreateTextureFromSurface(g_renderer, g_gameOver_surface);
	SDL_FreeSurface(g_gameOver_surface);


	// score
	font2 = TTF_OpenFont("../../Resources/arose.ttf", 50);

	
	

	TTF_CloseFont(font1);
	

	MakeItem();
}

Stage1::~Stage1()
{
	SDL_DestroyTexture(g_bg_texture);
	SDL_DestroyTexture(g_snake_texture);
	SDL_DestroyTexture(g_item_texture);
	SDL_DestroyTexture(g_gameOver_texture);
	SDL_DestroyTexture(g_score_texture);
	TTF_CloseFont(font2);
}

void Stage1::Update()
{
	g_elapsed_time_ms += 33;

	if(game_over==false)
		Move();
}

void Stage1::Move() {
	SDL_Rect snake_front_rect = snakeList.front().snake_rect;
	
	if (GetItem()) {
		score++;
		sprintf(g_score_array, "%d", score);
		g_score_char = g_score_array;
		AddSnake();
	}

	

	if (snake_state == 1) {
		// 왼쪽으로 이동
		// front에 한 개 추가, back에서 한 개 제거
		snakeList.pop_back();
		snakeList.push_front(Snake(snake_front_rect.x - 50, snake_front_rect.y));	// 50대신 GRID 안됨..
		SDL_Delay(160);
		if (snakeList.front().snake_rect.x <= 0) {
			snake_state = 0;
			game_over = true;
			
		}
		
	}
	else if (snake_state == 2) {
		// 오른쪽으로 이동
		snakeList.pop_back();
		snakeList.push_front(Snake(snake_front_rect.x + 50, snake_front_rect.y));	// 50대신 GRID 안됨..
		SDL_Delay(160);
		if (snakeList.front().snake_rect.x+50 >= 800) {
			snake_state = 0;
			game_over = true;
		}
		
	}
	else if (snake_state == 3) {
		// 위쪽으로 이동
		snakeList.pop_back();
		snakeList.push_front(Snake(snake_front_rect.x, snake_front_rect.y - 50));	// 50대신 GRID 안됨..
		SDL_Delay(160);
		if (snakeList.front().snake_rect.y <= 0) {
			snake_state = 0;
			game_over = true;
		}

	}
	else if (snake_state == 4) {
		// 아래쪽으로 이동
		snakeList.pop_back();
		snakeList.push_front(Snake(snake_front_rect.x, snake_front_rect.y + 50));	// 50대신 GRID 안됨..
		SDL_Delay(160);
		if (snakeList.front().snake_rect.y+50 >= 700) {
			snake_state = 0;
			game_over = true;
		}

	}
	
	
}

bool Stage1::Overlap() {

	SDL_Rect snake_front_rect = snakeList.front().snake_rect;
	
	for (auto iter = snakeList.begin(); iter != snakeList.end(); iter++) {
		
		
	}
	

}

bool Stage1::GetItem() {
	SDL_Rect snake_front_rect = snakeList.front().snake_rect;

	if (snake_front_rect.x == g_item_destination_rect.x && snake_front_rect.y == g_item_destination_rect.y) {
		MakeItem();
		return true;
	}
}

void Stage1::MakeItem() {
	srand((unsigned int)time(NULL));	// seed로 현재 시간 부여
	int x = rand() % 16;				// x는 750까지 가능
	int y = rand() % 14;				// y는 650까지 가능


	g_item_destination_rect.x = x * 50;
	g_item_destination_rect.y = y * 50;

}

void Stage1::Render()
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	// BG
	//SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);
	SDL_SetRenderDrawColor(g_renderer, 200, 191, 231, 255);

	// item
	SDL_RenderCopy(g_renderer, g_item_texture, &g_item_source_rect, &g_item_destination_rect);

	// snake
	for (auto iter = snakeList.begin(); iter != snakeList.end(); iter++) {
		SDL_RenderCopy(g_renderer, g_snake_texture, &g_snake_source_rect, &iter->snake_rect);
	}


	// score
	
	g_score_surface = TTF_RenderText_Blended(font2, g_score_char, black_100);

	g_score_rect.x = 0;
	g_score_rect.y = 0;
	g_score_rect.w = g_score_surface->w;
	g_score_rect.h = g_score_surface->h;

	g_score_texture = SDL_CreateTextureFromSurface(g_renderer, g_score_surface);
	SDL_FreeSurface(g_score_surface);
	

	g_score_destination_rect.x = 100;
	g_score_destination_rect.y = 400;
	g_score_destination_rect.w = g_score_rect.w;
	g_score_destination_rect.h = g_score_rect.h;
	
	
	SDL_RenderCopy(g_renderer, g_score_texture, &g_score_rect, &g_score_destination_rect);
	
	// game over
	if (game_over == true) {
		SDL_RenderCopy(g_renderer, g_gameOver_texture, &g_gameOver_rect, &g_gameOver_destination_rect);

	}

	SDL_RenderPresent(g_renderer); // draw to the screen
}



// snake 추가하기
void Stage1::AddSnake() {
	
	SDL_Rect snake_back_rect = snakeList.back().snake_rect;
	//snakeList.push_front(Snake());

	if (snake_state == 1) {
		// 왼쪽으로 움직이고 있었을 때
		snakeList.push_back(Snake(snake_back_rect.x + 50, snake_back_rect.y));
	}
	else if (snake_state == 2) {
		// 오른쪽으로 움직이고 있었을 때
		snakeList.push_back(Snake(snake_back_rect.x - 50, snake_back_rect.y));
	}
	else if (snake_state == 3) {
		// 위쪽으로 움직이고 있었을 때
		snakeList.push_back(Snake(snake_back_rect.x, snake_back_rect.y + 50));
	}
	else if (snake_state == 4) {
		// 아래쪽으로 움직이고 있었을 때
		snakeList.push_back(Snake(snake_back_rect.x, snake_back_rect.y - 50));
	}
}



void Stage1::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			// If the left arrow key is pressed. 
			if ( event.key.keysym.sym == SDLK_LEFT )
			{
				//cout << "snake state : 1";
				if(game_over==false)
					snake_state = 1;
			}
			else if ( event.key.keysym.sym == SDLK_RIGHT )
			{
				if (game_over == false)
					snake_state = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				if (game_over == false)
					snake_state = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if (game_over == false)
					snake_state = 4;
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				

			}
			/*
			else if (event.key.keysym.sym == SDLK_q)
			{
				AddSnake();
			}
			*/
			break;

		case SDL_KEYUP:
			if ( event.key.keysym.sym == SDLK_LEFT )
			{
			
			}
			else if ( event.key.keysym.sym == SDLK_RIGHT )
			{
				
			}
			break;
		

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if ( event.button.button == SDL_BUTTON_LEFT )
			{
				if (game_over == true) {
					g_current_game_phase = PHASE_ENDING;
				}
			}
			break;

		default:
			break;
		}
	}
}
