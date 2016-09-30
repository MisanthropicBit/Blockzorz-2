#ifndef GAME_STATE_OPTIONS_H
#define GAME_STATE_OPTIONS_H

#include "GameState.h"
#include "SlideBar.h"
#include "Font.h"
#include "Button.h"
#include "OptionButton.h"

class GameStateOptions : public GameState
{
	public:
		GameStateOptions();
		~GameStateOptions();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);
		void OnLeftButtonUp(int mx, int my);

	private:
		Font font;
		SDL_Surface* EyeCandy;
		SDL_Surface* Title;
		SDL_Surface* Cursor;
		SDL_Surface* Music;
		SDL_Surface* Sound;
		SDL_Surface* VideoMode;

		Button backbutton;
		SlideBar musicvolume;
		SlideBar soundvolume;
		OptionButton videomode;
		bool fullscreen;
		int mvolume;
		int svolume;
		int selected;

		int titlex;
		int cx;
		int cy;
		float offsetx;
		float offsety;
		float angle;
};

#endif