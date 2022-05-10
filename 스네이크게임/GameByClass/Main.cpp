#include "GameClass.h"
#include "Main.h"

Stage1::Stage1()
{

	
}

Stage1::~Stage1()
{
	SDL_DestroyTexture(texture_);
}

void Stage1::Update()
{

}


void Stage1::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255,255,255,0);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	

	SDL_RenderPresent(g_renderer); // draw to the screen
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
			
			}
			else if ( event.key.keysym.sym == SDLK_RIGHT )
			{
			
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				g_current_game_phase = PHASE_ENDING;
			}
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
				
			}
			break;

		default:
			break;
		}
	}
}
