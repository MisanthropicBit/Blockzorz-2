#ifndef BLOCKZORZ2_GAME_HPP
#define BLOCKZORZ2_GAME_HPP

#include <SDL.h>
#include "game_state.hpp"
#include "game_state_intro.hpp"
#include "timer.hpp"
#include "font.hpp"
#include <string>

const std::string VERSION = "v1.2b";
const float DESIRED_FPS   = 60.f;

class game {
	public:
		game();
		~game();

		int run();
		bool initialize();
		void handle_event();
		void update();
		void draw();
		void clean_up();

		SDL_Event event;
		timer game_timer;
		font debug_text;

		static settings game_settings;

	private:
};

#endif
