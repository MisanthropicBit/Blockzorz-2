#ifndef BLOCKZORZ2_GAME_STATE_HOW_TO_PLAY_HPP
#define BLOCKZORZ2_GAME_STATE_HOW_TO_PLAY_HPP

#include "game_state.hpp"
#include "button.hpp"

class game_state_howtoplay : public game_state {
	public:
		game_state_howtoplay();
		~game_state_howtoplay();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();
		
		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int dx, int dy, Uint8 state);
		void left_button_down(int mx, int my);

	private:
		int titlex;
		int textx;
		int texty;
		int cx;
		int cy;
		float offsetx;
		float offsety;
		float angle;

		button back_button;

		SDL_Surface* eye_candy;
		SDL_Surface* title;
		SDL_Surface* cursor;
		SDL_Surface* line1;
		SDL_Surface* line2;
		SDL_Surface* line3;
		SDL_Surface* line4;
		SDL_Surface* line5;
		SDL_Surface* line6;
		SDL_Surface* line7;
		SDL_Surface* line8;
};

#endif
