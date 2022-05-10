#pragma once

#include "SDL.h"


class Ending
{
public:
	Ending();
	~Ending();
	void HandleEvents();
	void Update();
	void Render();

private:
	// Title
	SDL_Texture* title_texture_;
	SDL_Rect title_source_rect_;
	SDL_Rect title_destination_rect_;


	// Restart Button
	SDL_Texture* restart_texture_;
	SDL_Rect restart_source_rect_;
	SDL_Rect restart_destination_rect_;
};


