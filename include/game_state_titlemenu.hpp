#ifndef BLOCKZORZ2_GAME_STATE_TITLE_MENU_HPP
#define BLOCKZORZ2_GAME_STATE_TITLE_MENU_HPP

#include <SDL.h>
#include "game_state.hpp"

class game_state_title_menu : public game_state {
	public:
		game_state_title_menu(const std::string& textfile);
		~game_state_title_menu();

		bool load();
		void handle_event();
		void update(int dt);
		void draw();
		void unload();

		SDL_Surface* Background;
		SDL_Surface* title;
};

#endif
