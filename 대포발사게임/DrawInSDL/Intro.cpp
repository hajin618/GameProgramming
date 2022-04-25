#include "GameFunc.h"
#include "Intro.h"
#include <windows.h>

void Init_Intro()
{

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
	// Phase Test
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 255, 255);
	SDL_RenderClear(g_renderer);
	SDL_RenderPresent(g_renderer);
}


void Clear_Intro()
{

}