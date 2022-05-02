#include "GameFunc.h"
#include "Intro.h"
#include <windows.h>

// BG
SDL_Rect g_intro_bg_source_rect;
SDL_Rect g_intro_bg_destination_rect;
SDL_Texture* g_intro_bg_texture;

// Font
SDL_Rect g_intro_font_rect;
SDL_Texture* g_intro_font_texture;

// Music
Mix_Music* g_intro_bg_music;

void Init_Intro()
{
	// BG
	SDL_Surface* bg_surface = IMG_Load("../../Resources/Intro.jpg");
	g_intro_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	// 잘라오는 곳의 사각형 (BG)
	g_intro_bg_source_rect.x = 0;
	g_intro_bg_source_rect.y = 0;
	g_intro_bg_source_rect.w = 320;
	g_intro_bg_source_rect.h = 230;

	// 붙일 곳의 사각형 (BG)
	g_intro_bg_destination_rect.x = 0;
	g_intro_bg_destination_rect.y = 0;
	g_intro_bg_destination_rect.w = 800;
	g_intro_bg_destination_rect.h = 500;





	// Font : Game Start
	TTF_Font* font1 = TTF_OpenFont("../../Resources/arose.ttf", 100);
	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Surface* tmp_surface = TTF_RenderText_Blended(font1, "Game Start", black);

	g_intro_font_rect.x = 0;
	g_intro_font_rect.y = 0;
	g_intro_font_rect.w = tmp_surface->w;
	g_intro_font_rect.h = tmp_surface->h;

	g_intro_font_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);
	TTF_CloseFont(font1);



	// 배경음악 로드
	g_intro_bg_music= Mix_LoadMUS("../../Resources/intro_bg_music.mp3");
	if (g_intro_bg_music == 0) {
		std::cout << "Mix_LoadMUS(\"intro_bg_music.mp3\"): " << Mix_GetError() << std::endl;
	}
	// 배경음악의 default 볼륨 크기 (0~128)
	Mix_VolumeMusic(128);
	// 배경음악 재생 (fade : 점점 크게)
	Mix_FadeInMusic(g_intro_bg_music, -1, 2000);
}

void HandleEvents_Intro()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			g_flag_running = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				g_current_game_phase = PHASE_MAIN;
			}
		}
	}

}

void Update_Intro() 
{

}

void Render_Intro()
{
	SDL_RenderClear(g_renderer);
	// Phase Test
	SDL_RenderCopy(g_renderer, g_intro_bg_texture, &g_intro_bg_source_rect, &g_intro_bg_destination_rect);
	SDL_RenderPresent(g_renderer);

	SDL_Rect tmp_r;
	tmp_r.x = 100;
	tmp_r.y = 100;
	tmp_r.w = g_intro_font_rect.w;
	tmp_r.h = g_intro_font_rect.h;
	SDL_RenderCopy(g_renderer, g_intro_font_texture, &g_intro_font_rect, &tmp_r);
	SDL_RenderPresent(g_renderer);
}


void Clear_Intro()
{
	SDL_DestroyTexture(g_intro_bg_texture);
	SDL_DestroyTexture(g_intro_font_texture);
	Mix_FreeMusic(g_intro_bg_music);
}