#include "GameClass.h"
#include "Ending.h"


Ending::Ending()
{
	// For Texture
	
	SDL_Surface* temp_surface = IMG_Load("../../Resources/ending_title.png");
	title_texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	title_source_rect_.x = 0;
	title_source_rect_.y = 0;
	title_source_rect_.w = 2544;
	title_source_rect_.h = 636;

	title_destination_rect_.x = 50;
	title_destination_rect_.y = 50;
	title_destination_rect_.w = title_source_rect_.w / 4;
	title_destination_rect_.h = title_source_rect_.h / 4;



	// Start Button
	SDL_Surface* restart_surface = IMG_Load("../../Resources/ending_restart.png");
	restart_texture_ = SDL_CreateTextureFromSurface(g_renderer, restart_surface);
	SDL_FreeSurface(restart_surface);

	restart_source_rect_.x = 0;
	restart_source_rect_.y = 0;
	restart_source_rect_.w = 986;
	restart_source_rect_.h = 449;

	restart_destination_rect_.x = 300;
	restart_destination_rect_.y = 400;
	restart_destination_rect_.w = restart_source_rect_.w / 4;
	restart_destination_rect_.h = restart_source_rect_.h / 4;
}

Ending::~Ending()
{
	SDL_DestroyTexture(title_texture_);
}

void Ending::Update()
{
}


void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255,255,255,255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, title_texture_, &title_source_rect_, &title_destination_rect_);
	SDL_RenderCopy(g_renderer, restart_texture_, &restart_source_rect_, &restart_destination_rect_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Ending::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if ( event.button.button == SDL_BUTTON_LEFT )
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x > restart_destination_rect_.x &&
					mouse_y > restart_destination_rect_.y &&
					mouse_x < restart_destination_rect_.x + restart_destination_rect_.w &&
					mouse_y < restart_destination_rect_.y + restart_destination_rect_.h)
				{
					g_current_game_phase = PHASE_INTRO;
				}
			}
			break;

		default:
			break;
		}
	}
}
