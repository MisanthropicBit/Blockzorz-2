#ifndef BLOCKZORZ2_GAME_STATE_OPTIONS_HPP
#define BLOCKZORZ2_GAME_STATE_OPTIONS_HPP

#include "game_state.hpp"
#include "slide_bar.hpp"
#include "font.hpp"
#include "button.hpp"
#include "option_button.hpp"

class game_state_options : public game_state {
	public:
		game_state_options();
		~game_state_options();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);
		void left_button_up(int mx, int my);

	private:
		font font;
		SDL_Surface* eye_candy;
		SDL_Surface* title;
		SDL_Surface* cursor;
		SDL_Surface* music;
		SDL_Surface* sound;
		SDL_Surface* videomode;

		button back_button;
		slide_bar music_volume;
		slide_bar sound_volume;
        option_button videomode;
		bool fullscreen;
		int music_volume;
		int sound_volume;
		int selected;
		int titlex;
		int cx;
		int cy;
		float offsetx;
		float offsety;
		float angle;
};

#endif
