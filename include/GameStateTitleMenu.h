#ifndef GAME_STATE_TITLE_MENU_H
#define GAME_STATE_TITLE_MENU_H

#include "GameState.h" // Parent

#include "SDL.h"

class GameStateTitleMenu : public GameState
{
	public:
		GameStateTitleMenu(const string& textfile);
		~GameStateTitleMenu();

		bool Load();
		void HandleEvent();
		void Update(int dt);
		void Draw();
		void UnLoad();

		SDL_Surface* BackGround;
		SDL_Surface* Title;
};

#endif