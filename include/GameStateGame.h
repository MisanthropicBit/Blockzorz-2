#ifndef GAME_STATE_GAME_H
#define GAME_STATE_GAME_H

#include "GameState.h"
#include "Timer.h"
#include "Font.h"
#include "Player.h"
#include "Button.h"
#include "ParticleEffectManager.h"

class GameStateGame : public GameState
{
	public:
		GameStateGame();
		~GameStateGame();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);

	private:
		Font font;
		Timer clock;
		Button quit;
		AnimatedButton musicbutton;
		AnimatedButton soundbutton;
		bool gamestarted;
		bool enterhighscore;

		Player player;

		SDL_Surface* EyeCandy;
		SDL_Surface* Gamefield;
		SDL_Surface* Arrow;
		SDL_Surface* Score;
		SDL_Surface* Time;
		SDL_Surface* Combos;
};

#endif