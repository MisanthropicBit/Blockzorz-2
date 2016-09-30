#ifndef GAME_STATE_HOW_TO_PLAY_H
#define GAME_STATE_HOW_TO_PLAY_H

#include "GameState.h"
#include "Button.h"

class GameStateHowToPlay : public GameState
{
	public:
		GameStateHowToPlay();
		~GameStateHowToPlay();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();
		
		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);

	private:
		int titlex;
		int textx;
		int texty;

		int cx;
		int cy;
		float offsetx;
		float offsety;
		float angle;

		Button backbutton;

		SDL_Surface* EyeCandy;
		SDL_Surface* Title;
		SDL_Surface* Cursor;
		SDL_Surface* Line1;
		SDL_Surface* Line2;
		SDL_Surface* Line3;
		SDL_Surface* Line4;
		SDL_Surface* Line5;
		SDL_Surface* Line6;
		SDL_Surface* Line7;
		SDL_Surface* Line8;
};


#endif