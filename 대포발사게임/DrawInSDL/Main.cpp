#include "Main.h"
#include "GameFunc.h"
#include <windows.h>
#include <vector>
#include <atlstr.h>
#include <string>

int g_elapsed_time_ms;

int man_x, man_y;
bool man_state[10];		// man 상태
						// 0 : stop
						// 1 : moving leftward
						// 2 : moving rightward
						// 3 : moving upward
						// 4 : moving downward

// 미사일 개수
int cnt_missile;

// 우주선 탑승여부
bool onSpaceship;

// BG
SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;

// man
SDL_Rect g_man_source_rect;
SDL_Rect g_man_destination_rect;
SDL_Texture* g_man_texture;

// box
SDL_Rect g_box_source_rect;
SDL_Rect g_box_destination_rect;
SDL_Texture* g_box_texture;

// cannon
SDL_Rect g_cannon_source_rect;
SDL_Rect g_cannon_destination_rect;
SDL_Texture* g_cannon_texture;




void Init_Main() {
	g_elapsed_time_ms = 0;
	cnt_missile = 0;
	
	man_x = 200;
	man_y = 130;

	onSpaceship = false;


	// BG 
	SDL_Surface* bg_surface = IMG_Load("../../Resources/main.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	// 잘라오는 곳의 사각형 (BG)
	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 860;
	g_bg_source_rect.h = 430;

	// 붙일 곳의 사각형
	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 800;
	g_bg_destination_rect.h = 500;



	// Man
	SDL_Surface* man_surface = IMG_Load("../../Resources/character.jpg");
	SDL_SetColorKey(man_surface, SDL_TRUE, SDL_MapRGB(man_surface->format, 255, 255, 255));
	g_man_texture = SDL_CreateTextureFromSurface(g_renderer, man_surface);
	SDL_FreeSurface(man_surface);

	// 잘라오는 곳의 사각형 (BG)
	g_man_source_rect.x = 35;
	g_man_source_rect.y = 0;
	g_man_source_rect.w = 180;
	g_man_source_rect.h = 276;

	// 붙일 곳의 사각형 (BG)
	g_man_destination_rect.x = 200;
	g_man_destination_rect.y = 130;
	g_man_destination_rect.w = g_man_source_rect.w/4;
	g_man_destination_rect.h = g_man_source_rect.h/4;



	// box
	SDL_Surface* box_surface = IMG_Load("../../Resources/box.jpg");
	SDL_SetColorKey(box_surface, SDL_TRUE, SDL_MapRGB(box_surface->format, 255, 255, 255));
	g_box_texture = SDL_CreateTextureFromSurface(g_renderer, box_surface);
	SDL_FreeSurface(box_surface);

	// 잘라오는 곳의 사각형
	g_box_source_rect.x = 0;
	g_box_source_rect.y = 20;
	g_box_source_rect.w = 256;
	g_box_source_rect.h = 272;

	// 붙일 곳의 사각형
	g_box_destination_rect.x = 50;
	g_box_destination_rect.y = 50;
	g_box_destination_rect.w = g_box_source_rect.w/4;
	g_box_destination_rect.h = g_box_source_rect.h/4;



	// cannon
	SDL_Surface* cannon_surface = IMG_Load("../../Resources/spaceship.png");
	SDL_SetColorKey(cannon_surface, SDL_TRUE, SDL_MapRGB(cannon_surface->format, 255, 255, 255));
	g_cannon_texture = SDL_CreateTextureFromSurface(g_renderer, cannon_surface);
	SDL_FreeSurface(cannon_surface);

	// 잘라오는 곳의 사각형
	g_cannon_source_rect.x = 253;
	g_cannon_source_rect.y = 83;
	g_cannon_source_rect.w = 495;
	g_cannon_source_rect.h = 834;

	// 붙일 곳의 사각형
	g_cannon_destination_rect.x = 350;
	g_cannon_destination_rect.y = 200;
	g_cannon_destination_rect.w = g_cannon_source_rect.w / 5;
	g_cannon_destination_rect.h = g_cannon_source_rect.h / 5;
}

void HandleEvents_Main() {
	
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			g_flag_running = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_LEFT) {
				man_state[1] = true;
				if (onSpaceship == true) {
					cnt_missile -= 1;
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				man_state[2] = true;
				if (onSpaceship == true) {
					cnt_missile -= 1;
				}
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				man_state[3] = true;
				if (onSpaceship == true) {
					cnt_missile -= 1;
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				man_state[4] = true;
				if (onSpaceship == true) {
					cnt_missile -= 1;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (cnt_missile == 0) {
					if (man_x > g_box_destination_rect.x - g_man_destination_rect.w &&
						man_x<g_box_destination_rect.x + g_box_destination_rect.w &&
						man_y>g_box_destination_rect.y - g_man_destination_rect.h &&
						man_y < g_box_destination_rect.y + g_box_destination_rect.h)
					{
						cnt_missile = 5;
					}
				}
				if (onSpaceship == true) {
					onSpaceship = false;
					man_x = 300;
					man_y = 150;
				}
				else if (onSpaceship == false) {
					if (man_x > g_cannon_destination_rect.x - g_man_destination_rect.w &&
						man_x<g_cannon_destination_rect.x + g_cannon_destination_rect.w &&
						man_y>g_cannon_destination_rect.y - g_man_destination_rect.h &&
						man_y < g_cannon_destination_rect.y + g_cannon_destination_rect.h)
					{
						onSpaceship = true;
						
						//탑승중 출력
					}
				}

			
			}
		}
		else if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_LEFT) {
				man_state[1] = false;
			
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				man_state[2] = false;
			
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				man_state[3] = false;
				
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				man_state[4] = false;
				
			}
		
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				g_current_game_phase = PHASE_ENDING;
			}
		}
		
	}
}

void Update_Main() {
	
	g_man_destination_rect.x = man_x;
	g_man_destination_rect.y = man_y;

	if (man_state[1] == true) {
		man_x -= 10;
	}
	if (man_state[2] == true) {
		man_x += 10;
	}
	if (man_state[3] == true) {
		man_y -= 10;
	}
	if (man_state[4] == true) {
		man_y += 10;
	}

	if (man_x >= 800) {
		man_x = 800;
	}
	else if (man_x <= 0) {
		man_x = 0;
	}
	if (man_y >= 500) {
		man_y = 500;
	}
	else if (man_y <= 0) {
		man_y = 0;
	}


	if (cnt_missile < 0) {
		cnt_missile = 0;
	}
	g_elapsed_time_ms += 33;
}

void Render_Main() {
	SDL_RenderClear(g_renderer);

	// BG
	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);

	// Box
	if (cnt_missile == 0)
		SDL_RenderCopy(g_renderer, g_box_texture, &g_box_source_rect, &g_box_destination_rect);

	// Cannon
	SDL_RenderCopy(g_renderer, g_cannon_texture, &g_cannon_source_rect, &g_cannon_destination_rect);

	// Man
	if(onSpaceship==false)
		SDL_RenderCopy(g_renderer, g_man_texture, &g_man_source_rect, &g_man_destination_rect);

	SDL_RenderPresent(g_renderer);
}

void Clear_Main() {
	SDL_DestroyTexture(g_bg_texture);
	SDL_DestroyTexture(g_man_texture);
	SDL_DestroyTexture(g_box_texture);
	SDL_DestroyTexture(g_cannon_texture);
}