#include "Ending.h"
#include "GameFunc.h"

void Init_Ending()
{

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
	// Phase Test
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
	SDL_RenderClear(g_renderer);
	SDL_RenderPresent(g_renderer);

}

void Clear_Ending()
{

}