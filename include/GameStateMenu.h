#ifndef BLOCKZORZ2_GAME_STATE_MENU_HPP
#define BLOCKZORZ2_GAME_STATE_MENU_HPP

#include "game_state.hpp"
#include "button.hpp"

class game_state_menu : public game_state {
	public:
		game_state_menu();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void key_dow(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);

	private:
		SDL_Surface* eye_candy;
		SDL_Surface* title;
		SDL_Surface* cursor;
		SDL_Surface* popup;

		button buttons[5];
		int selected;
		int titlex;
		int cx;
		int cy;
		float xoffset;
		float yoffset;
		float angle;
};

#endif
