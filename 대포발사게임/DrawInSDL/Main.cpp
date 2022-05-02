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


int m_x_vector[150];
int m_y_vector[150];
int m_state[150];		// missile 상태
						// 0 : stop
						// 1 : left
						// 2 : right
						// 3 : up
						// 4 : down
int g_m_point = 0;

// 우주선 탑승여부
bool onSpaceship;

// 우주선 각도
int cannon_angle;

// 미사일 각도
int missile_angle[150];

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

// missile
SDL_Rect g_missile_source_rect;
SDL_Rect g_missile_destination_rect;
SDL_Texture* g_missile_texture;

// 탑승중 표시
SDL_Rect g_onSpaceship_rect;
SDL_Texture* g_onSpaceship_texture;
SDL_Surface* onSpaceship_surface;

// font
TTF_Font* font1;
SDL_Color yellow = { 255,242,0,0 };

// 미사일 개수
int cnt_missile;
const char* cnt_missile_char;
char cnt_missile_array[5];

// 미사일 개수 출력
SDL_Rect g_cnt_missile_rect;
SDL_Texture* g_cnt_missile_texture;

// 효과음
Mix_Chunk* g_gun_sound;
Mix_Chunk* g_get_on_off;
Mix_Chunk* g_get_item;

void Init_Main() {
	g_elapsed_time_ms = 0;

	cnt_missile = 0;
	sprintf(cnt_missile_array, "%d", cnt_missile);
	cnt_missile_char = cnt_missile_array;

	man_x = 200;
	man_y = 130;

	onSpaceship = false;
	cannon_angle = 0;
	g_m_point = 0;
	m_state[g_m_point] = 0;

	// 확인
	g_flag_running = true;

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



	// missile
	SDL_Surface* missile_surface = IMG_Load("../../Resources/bullet.png");
	SDL_SetColorKey(missile_surface, SDL_TRUE, SDL_MapRGB(missile_surface->format, 255, 255, 255));
	g_missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);

	// 잘라오는 곳의 사각형
	g_missile_source_rect.x = 160;
	g_missile_source_rect.y = 0;
	g_missile_source_rect.w = 185;
	g_missile_source_rect.h = 512;

	// 붙일 곳의 사각형
	g_missile_destination_rect.x = 400;
	g_missile_destination_rect.y = 250;
	g_missile_destination_rect.w = g_missile_source_rect.w/7;
	g_missile_destination_rect.h = g_missile_source_rect.h/7;

	

	// 탑승중 표시
	font1 = TTF_OpenFont("../../Resources/arose.ttf", 30);
	onSpaceship_surface= TTF_RenderUTF8_Blended(font1, CW2A(L"탑승중", CP_UTF8), yellow);
	g_onSpaceship_rect.x = 0;
	g_onSpaceship_rect.y = 0;
	g_onSpaceship_rect.w = onSpaceship_surface->w;
	g_onSpaceship_rect.h = onSpaceship_surface->h;
	g_onSpaceship_texture= SDL_CreateTextureFromSurface(g_renderer, onSpaceship_surface);
	SDL_FreeSurface(onSpaceship_surface);
	TTF_CloseFont(font1);

	
	
	// 효과음 로드
	g_gun_sound = Mix_LoadWAV("../../Resources/missile_sound.WAV");
	g_get_on_off = Mix_LoadWAV("../../Resources/get_on_off.WAV");
	g_get_item = Mix_LoadWAV("../../Resources/get_item.WAV");
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
				
					cannon_angle = 270;

					if (cnt_missile > 0) {
						Mix_PlayChannel(-1, g_gun_sound, 0);
						cnt_missile -= 1;

						// 미사일 발사
						m_state[g_m_point] = 1;
						m_x_vector[g_m_point] = 300;
						m_y_vector[g_m_point] = 300;
						missile_angle[g_m_point] = 270;
						//std::cout << m_x_vector[g_m_point] << "  ";
						//std::cout << m_y_vector[g_m_point] << "\n";
						g_m_point++;

						sprintf(cnt_missile_array, "%d", cnt_missile);

					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				man_state[2] = true;
				if (onSpaceship == true) {
					
					cannon_angle = 90;

					if (cnt_missile > 0) {
						Mix_PlayChannel(-1, g_gun_sound, 0);
						cnt_missile -= 1;

						// 미사일 발사
						m_state[g_m_point] = 2;
						m_x_vector[g_m_point] = 450;
						m_y_vector[g_m_point] = 280;
						missile_angle[g_m_point] = 90;
						//std::cout << m_x_vector[g_m_point] << "  ";
						//std::cout << m_y_vector[g_m_point] << "\n";
						g_m_point++;

						sprintf(cnt_missile_array, "%d", cnt_missile);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				man_state[3] = true;
				if (onSpaceship == true) {
				
					cannon_angle = 0;

					if (cnt_missile > 0) {
						Mix_PlayChannel(-1, g_gun_sound, 0);
						cnt_missile -= 1;

						// 미사일 발사
						m_state[g_m_point] = 3;
						m_x_vector[g_m_point] = 400;
						m_y_vector[g_m_point] = 200;
						missile_angle[g_m_point] = 0;
						g_m_point++;

						sprintf(cnt_missile_array, "%d", cnt_missile);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				man_state[4] = true;
				if (onSpaceship == true) {
					
					cannon_angle = 180;

					if (cnt_missile > 0) {
						Mix_PlayChannel(-1, g_gun_sound, 0);
						cnt_missile -= 1;

						// 미사일 발사
						m_state[g_m_point] = 4;
						m_x_vector[g_m_point] = 400;
						m_y_vector[g_m_point] = 320;
						missile_angle[g_m_point] = 180;
						g_m_point++;

						sprintf(cnt_missile_array, "%d", cnt_missile);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (cnt_missile == 0) {
					if (man_x > g_box_destination_rect.x - g_man_destination_rect.w &&
						man_x<g_box_destination_rect.x + g_box_destination_rect.w &&
						man_y>g_box_destination_rect.y - g_man_destination_rect.h &&
						man_y < g_box_destination_rect.y + g_box_destination_rect.h)
					{
						Mix_PlayChannel(-1, g_get_item, 0);
						cnt_missile = 5;
						sprintf(cnt_missile_array, "%d", cnt_missile);
					}
				}
				if (onSpaceship == true) {
					onSpaceship = false;
					man_x = 380;
					man_y = 250;
					Mix_PlayChannel(-1, g_get_on_off, 0);
				}
				else if (onSpaceship == false) {
					if (man_x > g_cannon_destination_rect.x - g_man_destination_rect.w &&
						man_x<g_cannon_destination_rect.x + g_cannon_destination_rect.w &&
						man_y>g_cannon_destination_rect.y - g_man_destination_rect.h &&
						man_y < g_cannon_destination_rect.y + g_cannon_destination_rect.h)
					{
						onSpaceship = true;
						Mix_PlayChannel(-1, g_get_on_off, 0);
						
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

	g_missile_destination_rect.x = m_x_vector[g_m_point-1];
	g_missile_destination_rect.y = m_y_vector[g_m_point-1];

	if (man_state[1] == true) {
		man_x -= 8;
	}
	if (man_state[2] == true) {
		man_x += 8;
	}
	if (man_state[3] == true) {
		man_y -= 8;
	}
	if (man_state[4] == true) {
		man_y += 8;
	}

	if (man_x >= 760) {
		man_x = 760;
	}
	else if (man_x <= 0) {
		man_x = 0;
	}
	if (man_y >= 440) {
		man_y = 440;
	}
	else if (man_y <= 0) {
		man_y = 0;
	}


	if (cnt_missile < 0) {
		cnt_missile = 0;
	}

	for (int i = 0; i <= g_m_point; i++) {
		if (m_state[i] == 0) {

			m_x_vector[i] = 400;
			m_y_vector[i] = 250;
		}
		else if (m_state[i] == 1) {
			m_x_vector[i] -= 10;

			if (m_x_vector[i] <= -5)
				m_state[i] = 0;

		}
		
		else if (m_state[i] == 2) {
			m_x_vector[i] += 10;

			if (m_x_vector[i] >= 805)
				m_state[i] = 0;
		}
		else if (m_state[i] == 3) {
			m_y_vector[i] -= 10;

			if (m_y_vector[i] <= -5)
				m_state[i] = 0;
		}
		else if (m_state[i] == 4) {
			m_y_vector[i] += 10;

			if (m_y_vector[i] >= 505)
				m_state[i] = 0;
		}
		
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
	SDL_RenderCopyEx(g_renderer, g_cannon_texture, &g_cannon_source_rect, &g_cannon_destination_rect, cannon_angle, 0, SDL_FLIP_NONE);
	

	// Man
	if(onSpaceship==false)
		SDL_RenderCopy(g_renderer, g_man_texture, &g_man_source_rect, &g_man_destination_rect);

	// Missile
	for (int j = 0; j <= g_m_point; j++) {
		if (m_state[j] != 0) {
			SDL_Rect r = g_missile_destination_rect;
			r.x = m_x_vector[j];
			r.y = m_y_vector[j];
			SDL_RenderCopyEx(g_renderer, g_missile_texture, &g_missile_source_rect, &r, missile_angle[j], 0, SDL_FLIP_NONE);
		}
	}

	// 탑승중 출력
	if (onSpaceship == true) {
		SDL_Rect onSpaceship_tmp_r;
		onSpaceship_tmp_r.x = 50;
		onSpaceship_tmp_r.y = 450;
		onSpaceship_tmp_r.w = g_onSpaceship_rect.w;
		onSpaceship_tmp_r.h = g_onSpaceship_rect.h;
		SDL_RenderCopy(g_renderer, g_onSpaceship_texture, &g_onSpaceship_rect, &onSpaceship_tmp_r);
	}


	// 미사일 개수 출력
	TTF_Font* font1 = TTF_OpenFont("../../Resources/arose.ttf", 30);
	SDL_Color yellow = { 255,242,0,0 };

	SDL_Surface* cnt_missile_surface = TTF_RenderText_Blended(font1, cnt_missile_char, yellow);
	g_cnt_missile_rect.x = 0;
	g_cnt_missile_rect.y = 0;
	g_cnt_missile_rect.w = cnt_missile_surface->w;
	g_cnt_missile_rect.h = cnt_missile_surface->h;
	g_cnt_missile_texture = SDL_CreateTextureFromSurface(g_renderer, cnt_missile_surface);
	SDL_FreeSurface(cnt_missile_surface);
	TTF_CloseFont(font1);

	SDL_Rect cnt_missile_tmp_r;
	cnt_missile_tmp_r.x = 700;
	cnt_missile_tmp_r.y = 450;
	cnt_missile_tmp_r.w = g_cnt_missile_rect.w;
	cnt_missile_tmp_r.h = g_cnt_missile_rect.h;
	SDL_RenderCopy(g_renderer, g_cnt_missile_texture, &g_cnt_missile_rect, &cnt_missile_tmp_r);


	SDL_RenderPresent(g_renderer);
}

void Clear_Main() {
	SDL_DestroyTexture(g_bg_texture);
	SDL_DestroyTexture(g_man_texture);
	SDL_DestroyTexture(g_box_texture);
	SDL_DestroyTexture(g_cannon_texture);
	SDL_DestroyTexture(g_missile_texture);
	SDL_DestroyTexture(g_cnt_missile_texture);
	SDL_DestroyTexture(g_onSpaceship_texture);
	Mix_FreeChunk(g_gun_sound);
	Mix_FreeChunk(g_get_item);
	Mix_FreeChunk(g_get_on_off);
}