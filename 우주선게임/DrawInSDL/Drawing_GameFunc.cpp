#include "Drawing_GameFunc.h"
#include <windows.h>
#include <vector>
#include <atlstr.h>
#include <string>


int f_x, f_y;
bool f_state[10];
				// ���ּ� ����
				// 0 : stop
				// 1 : moving leftward
				// 2 : moving rightward
				// 3 : moving upward
				// 4 : moving downward

//int m_x, m_y;
int m_x_vector[130];
int m_y_vector[130];
int m_state[130];		// �̻��� ����
						// 0 : in Flight
						// 1 : Flying


int g_m_point = 0;
int g_m_use = 0;
int g_elapsed_time_ms;


// ����(�ѱ�)
SDL_Rect g_jumsu_rect;
SDL_Texture* g_jumsu_texture;


// ����(����)
SDL_Texture* g_score_texture;
SDL_Rect g_score_rect;
int g_score_int;
// �ּ��� �� ����x, �ּҰ� ���� ����
const char* g_score_char;
char g_score_array[10];



// ��� �׸� �ҽ��� �ش��ϴ� rect
SDL_Rect g_bg_source_rect;
// ���׸��� �ٿ� ���� �簢��
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;


//SDL_Rect g_char_pos;
SDL_Texture* g_ryu_sheet_texture;
SDL_Rect g_source_rect;
SDL_Rect g_destination_rect;


// �̻��� ���� ������
SDL_Texture* g_missile_texture;
SDL_Rect g_m_source_rect;
SDL_Rect g_m_destination_rect;

// ���� �����Ͱ�
Mix_Music* g_bg_mus;
Mix_Chunk* g_gun_sound;

void InitGame() {
	f_x = 200;
	f_y = 500;

	// int -> char
	g_score_int = 0;
	sprintf(g_score_array, "%d", g_score_int);
	if (strlen(g_score_array) == 1) {
		g_score_array[1] = '0';
		g_score_array[2] = '0';
		g_score_array[3] = '0';
		g_score_array[4] = '0';
	}
	g_score_char = g_score_array;

	//m_x = f_x;
	//m_y = f_y - 50;
	m_state[g_m_point] = 0;
	g_flag_running = true;
	g_elapsed_time_ms = 0;


	// ������� �ε�
	g_bg_mus = Mix_LoadMUS("../../Resources/bg_music.mp3");
	if (g_bg_mus == 0) {
		std::cout << "Mix_LoadMUS(\"Kalimba.mp3\"): " << Mix_GetError() << std::endl;
	}
	// ȿ���� �ε�
	g_gun_sound = Mix_LoadWAV("../../Resources/missile_sound.WAV");
	// ��������� default ���� ũ�� (0~128)
	Mix_VolumeMusic(128);
	// ������� ��� (fade : ���� ũ��)
	Mix_FadeInMusic(g_bg_mus, -1, 2000);



	// ���� : (�ѱ�)
	TTF_Font* font1 = TTF_OpenFont("../../Resources/arose.ttf", 20);
	SDL_Color red = { 255, 0, 0, 0 };
	SDL_Surface* tmp_jumsu_surface = TTF_RenderUTF8_Blended(font1, CW2A(L"���� : ", CP_UTF8), red);
	g_jumsu_rect.x = 0;
	g_jumsu_rect.y = 0;
	g_jumsu_rect.w = tmp_jumsu_surface->w;
	g_jumsu_rect.h = tmp_jumsu_surface->h;
	g_jumsu_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_jumsu_surface);
	SDL_FreeSurface(tmp_jumsu_surface);
	TTF_CloseFont(font1);
	



	// BG ����
	SDL_Surface* bg_surface = IMG_Load("../../Resources/31095.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	// �߶���� ���� �簢�� (BG)
	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 600;
	g_bg_source_rect.h = 1067;

	// ���� ���� �簢�� (BG)
	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = g_bg_source_rect.w;
	g_bg_destination_rect.h = g_bg_source_rect.h;



	// ���ּ�
	SDL_Surface* ryu_sheet_surface = IMG_Load("../../Resources/aaa.png");
	SDL_SetColorKey(ryu_sheet_surface, SDL_TRUE, SDL_MapRGB(ryu_sheet_surface->format, 255, 255, 255));
	g_ryu_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, ryu_sheet_surface);
	SDL_FreeSurface(ryu_sheet_surface);

	g_source_rect.x = 74;
	g_source_rect.y = 91;
	g_source_rect.w = 77;
	g_source_rect.h = 44;

	g_destination_rect.x = 200;
	g_destination_rect.y = 500;
	g_destination_rect.w = g_source_rect.w;
	g_destination_rect.h = g_source_rect.h;



	// �̻���
	SDL_Surface* missile_surface = IMG_Load("../../Resources/fff.png");
	SDL_SetColorKey(missile_surface, SDL_TRUE, SDL_MapRGB(missile_surface->format, 255, 255, 255));
	g_missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);

	g_m_source_rect.x = 73;
	g_m_source_rect.y = 2;
	g_m_source_rect.w = 100;
	g_m_source_rect.h = 190;

	g_m_destination_rect.x = g_destination_rect.x;
	g_m_destination_rect.y = g_destination_rect.y - 50;
	g_m_destination_rect.w = g_m_source_rect.w;
	g_m_destination_rect.h = g_m_source_rect.h;


}

void HandleEvents() {
	// Handle Events
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			g_flag_running = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_LEFT) {
				
				f_state[1] = true;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				
				f_state[2] = true;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
			
				f_state[3] = true;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
			
				f_state[4] = true;
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				
				m_state[g_m_point] = 1;
				m_x_vector[g_m_point] = f_x;
				m_y_vector[g_m_point] = f_y - 50;
				g_m_point++;
				g_score_int += 10;

				// int -> char*
				sprintf(g_score_array, "%d", g_score_int);
				
				// �ڸ��� 0���� ä���
				if (strlen(g_score_array) == 2) {
					char a = g_score_array[0];
					char b = g_score_array[1];
					for (int i = 0; i <= 2; i++) {
						g_score_array[i] = '0';
					}
					g_score_array[3] = a;
					g_score_array[4] = b;
				}
				else if (strlen(g_score_array) == 3) {
					char a = g_score_array[0];
					char b = g_score_array[1];
					char c = g_score_array[2];
					g_score_array[0] = '0';
					g_score_array[1] = '0';
					g_score_array[2] = a;
					g_score_array[3] = b;
					g_score_array[4] = c;
				}
				else if (strlen(g_score_array) == 4) {
					char a = g_score_array[0];
					char b = g_score_array[1];
					char c = g_score_array[2];
					char d = g_score_array[3];
					g_score_array[0] = '0';
					g_score_array[1] = a;
					g_score_array[2] = b;
					g_score_array[3] = c;
					g_score_array[4] = d;
				}

				g_score_char = g_score_array;

				std::cout <<"����(int): " << g_score_int << "   ����(char): " << g_score_char << std::endl;
				//std::cout << g_m_point << std::endl;
				// ȿ���� ���
				// (channel(-1�� �ϸ� ����� �� �ִ� ���� ���� ��ȣ ��� : �߰��� �ѹ� �� �������� ������ �ʰ� ��� �÷���), chunk, loops(0���� �ؾ� ��	�� ����))
				// ä�� Ȯ���ϰ� ������ int c=Mix_PlayChannel �� cout<<c
				Mix_PlayChannel(-1, g_gun_sound, 0);
			}
		}
		else if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_LEFT) {

				f_state[1] = false;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {

				f_state[2] = false;
			}
			else if (event.key.keysym.sym == SDLK_UP) {

				f_state[3] = false;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {

				f_state[4] = false;
			}
		
		}
	}
}

void Update() {
	g_destination_rect.x = f_x;
	g_destination_rect.y = f_y;

	g_m_destination_rect.x = m_x_vector[g_m_point];
	g_m_destination_rect.y = m_y_vector[g_m_point];

	

	
	

	if (f_state[1] == true) {
		f_x -= 10;
	}
	if (f_state[2] == true) {
		f_x += 10;
	}
	if (f_state[3] == true) {
		f_y -= 10;
	}
	if (f_state[4] == true) {
		f_y += 10;
	}

	if (f_x >= 523) {
		f_x = 523;
	}
	else if (f_x <= 0) {
		f_x = 0;
	}
	if (f_y >= 700) {
		f_y = 700;
	}
	else if (f_y <= 0) {
		f_y = 0;
	}


	
	for (int i = 0; i <= g_m_point; i++) {
		if (m_state[i] == 0) {

			m_x_vector[i] = f_x;
			m_y_vector[i] = f_y - 50;

		}

		else if (m_state[i] == 1) {

			m_y_vector[i] -= 10;

			if (m_y_vector[i] <= -5) {
				m_state[i] = 0;
			}

		}
	}
	
	// Update

	g_elapsed_time_ms += 33;
}

void Render() {

	// Background
	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);
	

	// ���ּ�
	SDL_RenderCopy(g_renderer, g_ryu_sheet_texture, &g_source_rect, &g_destination_rect);


	// �̻���
	for (int k = 0; k <= g_m_point; k++) {
		if (m_state[k] == 1) {
			for (int j = 0; j < 2; j++) {
				SDL_Rect r = g_m_destination_rect;
				r.x = m_x_vector[k];
				r.x += j * 55;
				r.y = m_y_vector[k];
				r.w = r.w * 0.2f;
				r.h = r.h * 0.2f;
				SDL_RenderCopy(g_renderer, g_missile_texture, &g_m_source_rect, &r);
			}
		}
	}
	
	// ����(�ѱ�)
	{
		SDL_Rect tmp_r;
		tmp_r.x = 10;
		tmp_r.y = 10;
		tmp_r.w = g_jumsu_rect.w;
		tmp_r.h = g_jumsu_rect.h;
		SDL_RenderCopy(g_renderer, g_jumsu_texture, &g_jumsu_rect, &tmp_r);
	}


	// ����(int)
	{
		// ��Ʈ ���� (���, ��Ʈ ũ��)
		TTF_Font* font1 = TTF_OpenFont("../../Resources/arose.ttf", 20);
		SDL_Color red = { 255, 0, 0, 0 };

		// blended, solid, shaded �����ڷ� ����
		SDL_Surface* tmp_surface = TTF_RenderText_Blended(font1, g_score_char, red);
		//SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font1, CW2A(L"���� : ", CP_UTF8), red);
		g_score_rect.x = 0;
		g_score_rect.y = 0;
		g_score_rect.w = tmp_surface->w;
		g_score_rect.h = tmp_surface->h;
		g_score_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(font1);

		SDL_Rect tmp_r;
		tmp_r.x = 70;
		tmp_r.y = 10;
		tmp_r.w = g_score_rect.w;
		tmp_r.h = g_score_rect.h;
		SDL_RenderCopy(g_renderer, g_score_texture, &g_score_rect, &tmp_r);

	}
	

	SDL_RenderPresent(g_renderer);
}

void ClearGame() {
	SDL_DestroyTexture(g_bg_texture);
	SDL_DestroyTexture(g_ryu_sheet_texture);
	SDL_DestroyTexture(g_missile_texture);

	// ������� �޸𸮿��� ����
	Mix_FreeMusic(g_bg_mus);
	// ȿ���� �޸𸮿��� ����
	Mix_FreeChunk(g_gun_sound);
}