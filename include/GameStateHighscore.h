#ifndef BLOCKZORZ2_GAME_STATE_HIGHSCORE_HPP
#define BLOCKZORZ2_GAME_STATE_HIGHSCORE_HPP

#include "game_state.hpp"
#include "game_state_popup.hpp"
#include "font.hpp"
#include "button.hpp"
#include <string>

const int MAX_HIGHSCORES = 10;
const int MAX_NAME_SIZE  = 10;

struct highscore {
    std::string name;
	std::string score;
	std::string combos;
	std::string mins;
	std::string secs;
};

class game_state_highscore : public game_state {
	public:
		game_state_highscore();
		~game_state_highscore();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);

		void save(const std::string& filename);
		bool load(const std::string& filename);
		int lowest() const;
		int score_position(int score);
		void pass_new_highscore(int position, const highscore& highscore);

	private:
		highscore highscores[10];
		font subtitle_font;
		font font;

		button back_button;

		SDL_Surface* eye_candy;
		SDL_Surface* title;
		SDL_Surface* cursor;
		SDL_Surface* gold_block;
		SDL_Surface* silver_block;
		SDL_Surface* bronze_block;

		int titlex;
		int cx;
		int cy;
		float offsetx;
		float offsety;
		float angle;
};

class game_state_enter_highscore : public game_state_popup {
	public:
		game_state_enter_highscore (const std::string& caption, int position, highscore score);
		~game_state_enter_highscore ();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);

	private:
		highscore score;
		button submit;
		font text_font;
		int position;
};

#endif
