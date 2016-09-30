#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "GameState.h"
#include "GameStateIntro.h"
#include "Timer.h"
#include "Font.h"
#include <string>
using namespace std;

//=========================================================================================================================

const string VERSION = "v1.2b";
const float DESIRED_FPS = 60.f;

//=========================================================================================================================

struct Settings
{
	int mvolume;
	int svolume;
	bool fullscreen;
	bool CFmodeunlocked;
};

//=========================================================================================================================

class Game
{
	public:
		Game();
		~Game();

		int Run();
		bool Initialize();
		void HandleEvent();
		void Think();
		void Draw();
		void CleanUp();

		SDL_Event event;
		Timer gametimer;
		Font debugtext;

		static Settings gamesettings;

	private:
		
};

//=========================================================================================================================

#endif