#ifndef BLOCKZORZ2_GAME_STATE_INTRO_HPP
#define BLOCKZORZ2_GAME_STATE_INTRO_HPP

#include "game_state.hpp"
#include <string>

enum intro_state {
	INTRO_STATE_FADING_IN = 0,
	INTRO_STATE_DISPLAYING,
	INTRO_STATE_FADING_OUT
};

class game_state_intro : public game_state {
	public:
		game_state_intro();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void reset();

		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void left_button_down(int mx, int my);

	private:
		SDL_Surface* logo;
		SDL_Surface* sdl_logo;
		SDL_Surface* fader;
        std::string sound_effect;
		int which_logo;
		float alpha;
		intro_state state;
		int update_interval;
		int fade_in_time;
		int display_time;
		int fadeout_time;
};

#endif
