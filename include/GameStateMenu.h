#ifndef GAME_STATE_MENU_H
#define GAME_STATE_MENU_H

#include "GameState.h"
#include "Button.h"

class GameStateMenu : public GameState
{
	public:
		GameStateMenu();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);

	private:
		SDL_Surface* EyeCandy;
		SDL_Surface* Title;
		SDL_Surface* Cursor;
		SDL_Surface* PopUp;

		Button buttons[5];
		int selected;

		int titlex;
		int cx;
		int cy;
		float offsetx;
		float offsety;
		float angle;
};

#endif