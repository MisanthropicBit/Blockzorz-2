#ifndef GAME_STATE_POP_UP
#define GAME_STATE_POP_UP

#include "GameState.h"
#include "Button.h"
#include "ParticleEffectManager.h"

class GameStatePopUp : public GameState
{
	public:
		GameStatePopUp();
		GameStatePopUp(const string& caption, const string& text, const string& confirmtext, const string& quittext, GameState* returnstate);
		~GameStatePopUp();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);

	private:
		Button Yes;
		Button No;

	protected:
		SDL_Surface* Fader;
		SDL_Surface* PopUp;
		SDL_Surface* Title;
		SDL_Surface* Text;

		int titlex;
		int textx;

		GameState* returnstate;
};

class GameStateModeUnlocked : public GameStatePopUp
{
	public:
		GameStateModeUnlocked();
		GameStateModeUnlocked(const string& caption, const string& text, GameState* returnstate);
		~GameStateModeUnlocked();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);

	private:
		ParticleEffectManager peManager;
		int particleinterval;

		Button awesome;

		GameState* returnstate;
};

#endif