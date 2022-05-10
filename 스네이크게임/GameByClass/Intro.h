#pragma once

#include "SDL.h"

class Intro
{
// publilc : 외부에서 참조 가능
public:
	// 클래스 이름과 함수 이름 똑같이 하면 생성자
	// (시작할 때 한번만 호출)
	Intro();
	// ~ : 끝날 때 호출되는 함수
	~Intro();
	void HandleEvents();
	void Update();
	void Render();

// private : 외부에서 참조 불가능
// 전역변수
private:
	// Title
	SDL_Texture* title_texture_; 
	SDL_Rect title_source_rect_; 
	SDL_Rect title_destination_rect_; 


	// Start Button
	SDL_Texture* start_texture_;
	SDL_Rect start_source_rect_;
	SDL_Rect start_destination_rect_;
};


