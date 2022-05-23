
#include "GameClass.h"
#include "Intro.h"
#include "Main.h"
#include "Ending.h"




/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

// Game Phases
int g_current_game_phase;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	g_window = SDL_CreateWindow("First Window", 100, 100, 800, 700, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	
	InitGame();

	// Intro.h private 변수 생성됨, 생성자 자동 호출
	Intro intro;
	Stage1 stage1;
	Ending ending;

	g_current_game_phase = PHASE_INTRO;

	while ( g_flag_running )
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if ( cur_time_ms-g_last_time_ms < 33 )
			continue;

		if ( g_current_game_phase ==  PHASE_INTRO )
		{
			Intro intro;
			ending.~Ending();
			while (g_current_game_phase == PHASE_INTRO) {
				intro.HandleEvents();
				SDL_Delay(3);
				intro.Update();
				SDL_Delay(3);
				intro.Render();
			}
			
		}
		else if ( g_current_game_phase == PHASE_STAGE1 )
		{
			Stage1 stage1;
			intro.~Intro();
			while (g_current_game_phase == PHASE_STAGE1) {
				stage1.HandleEvents();
				SDL_Delay(3);
				stage1.Update();
				SDL_Delay(3);
				stage1.Render();
			}
			
		}
		
		if ( g_current_game_phase == PHASE_ENDING )
		{
			Ending ending;
			stage1.~Stage1();
			while (g_current_game_phase == PHASE_ENDING) {
				ending.HandleEvents();
				SDL_Delay(3);
				ending.Update();
				SDL_Delay(3);
				ending.Render();
			}
			
		}
		
		g_last_time_ms = cur_time_ms;
		SDL_Delay(1);
	}

	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();


	return 0;
}


