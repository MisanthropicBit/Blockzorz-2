#ifndef GAME_STATE_INTRO_H
#define GAME_STATE_INTRO_H

//=========================================================================================================================

#include "GameState.h"

#include <string>
using namespace std;

//=========================================================================================================================

enum IntroState
{
	INTRO_STATE_FADING_IN,
	INTRO_STATE_DISPLAYING,
	INTRO_STATE_FADING_OUT
};

//=========================================================================================================================

class GameStateIntro : public GameState
{
	public:
		GameStateIntro();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void Reset();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnLeftButtonDown(int mx, int my);

	private:
		SDL_Surface* logo;
		SDL_Surface* SDL_logo;
		SDL_Surface* fader;
		string soundeffect;
		int whichlogo;
		float alpha;
		IntroState istate;
		int updateinterval;
		int fadeintime;
		int displaytime;
		int fadeouttime;
};

//=========================================================================================================================

#endif