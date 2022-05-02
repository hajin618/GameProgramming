#include "Main.h"
#include "GameFunc.h"
#include "Main.h"
#include "Ending.h"
#include "Intro.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

// Game Phases
int g_current_game_phase;


int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);

	// Text init
	TTF_Init();

	// 프로그램 시작할 때 Audio Open
	// frequency : 주파수	format,	channels,	chunksize
	// mix_dafault_frequency : 22050		44100(CD) 비교해보기
	// 0 : success, -1 : errors
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	g_window = SDL_CreateWindow("First Window", 100, 100, 800, 500, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);


	InitGame();

	Init_Intro();
	Init_Main();
	Init_Ending();

	g_current_game_phase = PHASE_INTRO;
	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		if (g_current_game_phase == PHASE_INTRO)
		{
			Init_Intro();
			Clear_Ending();
			while (g_current_game_phase == PHASE_INTRO) {
				HandleEvents_Intro();
				SDL_Delay(10);
				Update_Intro();
				SDL_Delay(10);
				Render_Intro();
				
			}
			
		}
		else if (g_current_game_phase == PHASE_MAIN)
		{
			Init_Main();
			Clear_Intro();
			while (g_current_game_phase == PHASE_MAIN) {
				HandleEvents_Main();
				SDL_Delay(10);
				Update_Main();
				SDL_Delay(10);
				Render_Main();
			}
			
		}
		else if (g_current_game_phase == PHASE_ENDING)
		{
			Init_Ending();
			Clear_Main();
			while (g_current_game_phase == PHASE_ENDING) {
				HandleEvents_Ending();
				SDL_Delay(10);
				Update_Ending();
				SDL_Delay(10);
				Render_Ending();
			}
		}

		g_last_time_ms = cur_time_ms;
	}

	Clear_Intro();
	Clear_Main();
	Clear_Ending();
	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);



	// 프로그램 끝날 때 Audio Close
	Mix_CloseAudio();

	// Text quit
	TTF_Quit();

	SDL_Quit();

	return 0;
}