#include "Ending.h"
#include "GameFunc.h"

// BG
SDL_Rect g_ending_bg_source_rect;
SDL_Rect g_ending_bg_destination_rect;
SDL_Texture* g_ending_bg_texture;

// Font
SDL_Rect g_ending_font_rect;
SDL_Texture* g_ending_font_texture;

// Music
Mix_Music* g_ending_bg_music;

void Init_Ending()
{
	// BG
	SDL_Surface* bg_surface = IMG_Load("../../Resources/ending.jpg");
	g_ending_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	// 잘라오는 곳의 사각형 (BG)
	g_ending_bg_source_rect.x = 0;
	g_ending_bg_source_rect.y = 0;
	g_ending_bg_source_rect.w = 550;
	g_ending_bg_source_rect.h = 440;

	// 붙일 곳의 사각형 (BG)
	g_ending_bg_destination_rect.x = 0;
	g_ending_bg_destination_rect.y = 0;
	g_ending_bg_destination_rect.w = 800;
	g_ending_bg_destination_rect.h = 500;



	// Font : Game Start
	TTF_Font* font1 = TTF_OpenFont("../../Resources/arose.ttf", 100);
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* tmp_surface = TTF_RenderText_Blended(font1, "Game Over", white);

	g_ending_font_rect.x = 0;
	g_ending_font_rect.y = 0;
	g_ending_font_rect.w = tmp_surface->w;
	g_ending_font_rect.h = tmp_surface->h;

	g_ending_font_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);
	TTF_CloseFont(font1);
}

void HandleEvents_Ending()
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
				g_current_game_phase = PHASE_INTRO;
			}
		}
	}
}

void Update_Ending()
{

}

void Render_Ending()
{
	SDL_RenderClear(g_renderer);
	// Phase Test
	
	SDL_RenderCopy(g_renderer, g_ending_bg_texture, &g_ending_bg_source_rect, &g_ending_bg_destination_rect);
	SDL_RenderPresent(g_renderer);

	SDL_Rect tmp_r;
	tmp_r.x = 100;
	tmp_r.y = 100;
	tmp_r.w = g_ending_font_rect.w;
	tmp_r.h = g_ending_font_rect.h;
	SDL_RenderCopy(g_renderer, g_ending_font_texture, &g_ending_font_rect, &tmp_r);
	SDL_RenderPresent(g_renderer);
}

void Clear_Ending()
{
	SDL_DestroyTexture(g_ending_bg_texture);
	SDL_DestroyTexture(g_ending_font_texture);
}