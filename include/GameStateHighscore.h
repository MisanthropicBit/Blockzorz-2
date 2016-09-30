#ifndef GAME_STATE_HIGHSCORE_H
#define GAME_STATE_HIGHSCORE_H

#include "GameState.h"
#include "GameStatePopUp.h"
#include "Font.h"
#include "Button.h"
#include <string>
using namespace std;

//=========================================================================================================================

const int MAX_HIGHSCORES = 10;
const int MAX_NAME_SIZE  = 10;

//=========================================================================================================================

struct Highscore
{
	string name;
	string score;
	string combos;
	string mins;
	string secs;
};

//=========================================================================================================================

class GameStateHighscore : public GameState
{
	public:
		GameStateHighscore();
		~GameStateHighscore();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);

		void SaveHighscores(const string& filename);
		bool LoadHighscores(const string& filename);
		int GetLowestHighscore() const;
		int GetScorePosition(int score);
		void PassNewHighscore(int position, Highscore highscore);

	private:
		Highscore Highscores[10];
		Font subtitlefont;
		Font font;

		Button backbutton;

		SDL_Surface* EyeCandy;
		SDL_Surface* Title;
		SDL_Surface* Cursor;
		SDL_Surface* GoldBlock;
		SDL_Surface* SilverBlock;
		SDL_Surface* BronzeBlock;

		int titlex;

		int cx;
		int cy;
		float offsetx;
		float offsety;
		float angle;
};

//=========================================================================================================================

class GameStateEnterHighscore : public GameStatePopUp
{
	public:
		GameStateEnterHighscore(const string& caption, int position, Highscore score);
		~GameStateEnterHighscore();

		bool Load();
		void OnEvent(SDL_Event& event);
		void Update(int dt);
		void Draw();
		void UnLoad();

		void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);

	private:
		Highscore score;
		Button submit;
		Font textfont;
		int position;
};

//=========================================================================================================================

#endif