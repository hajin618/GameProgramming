#include "GameClass.h"
#include "Intro.h"


Intro::Intro()
{
	
	// Title
	SDL_Surface* temp_surface = IMG_Load("../../Resources/intro_title.png");
	title_texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	title_source_rect_.x = 0;
	title_source_rect_.y = 0;
	title_source_rect_.w = 2798;
	title_source_rect_.h = 636;

	title_destination_rect_.x = 50;
	title_destination_rect_.y = 50;
	title_destination_rect_.w = title_source_rect_.w / 4;
	title_destination_rect_.h = title_source_rect_.h / 4;



	// Start Button
	SDL_Surface* start_surface = IMG_Load("../../Resources/intro_start.png");
	start_texture_ = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);

	start_source_rect_.x = 0;
	start_source_rect_.y = 0;
	start_source_rect_.w = 905;
	start_source_rect_.h = 415;

	start_destination_rect_.x = 300;
	start_destination_rect_.y = 400;
	start_destination_rect_.w = start_source_rect_.w / 4;
	start_destination_rect_.h = start_source_rect_.h / 4;
}

Intro::~Intro()
{
	SDL_DestroyTexture(title_texture_);
	SDL_DestroyTexture(start_texture_);
}

void Intro::Update()
{
}


void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 200,191,231,255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, title_texture_, &title_source_rect_, &title_destination_rect_);
	SDL_RenderCopy(g_renderer, start_texture_, &start_source_rect_, &start_destination_rect_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Intro::HandleEvents()
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

				if (mouse_x > start_destination_rect_.x &&
					mouse_y > start_destination_rect_.y &&
					mouse_x < start_destination_rect_.x + start_destination_rect_.w &&
					mouse_y < start_destination_rect_.y + start_destination_rect_.h)
				{
					g_current_game_phase = PHASE_STAGE1;
				}
				
			}
			break;

		default:
			break;
		}
	}
}
