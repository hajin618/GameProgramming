#pragma once

#include "SDL.h"

class Intro
{
// publilc : �ܺο��� ���� ����
public:
	// Ŭ���� �̸��� �Լ� �̸� �Ȱ��� �ϸ� ������
	// (������ �� �ѹ��� ȣ��)
	Intro();
	// ~ : ���� �� ȣ��Ǵ� �Լ�
	~Intro();
	void HandleEvents();
	void Update();
	void Render();

// private : �ܺο��� ���� �Ұ���
// ��������
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


