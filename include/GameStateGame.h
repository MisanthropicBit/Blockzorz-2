#ifndef BLOCKZORZ2_GAME_STATE_GAME_HPP
#define BLOCKZORZ2_GAME_STATE_GAME_HPP

#include "game_state.hpp"
#include "timer.hpp"
#include "font.hpp"
#include "player.hpp"
#include "button.hpp"
#include "particle_effect_manager.hpp"

class game_state_game : public game_state {
	public:
		game_state_game();
		~game_state_game();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);

	private:
		font font;
		timer clock;
		button quit;
		animated_button music_button;
		animated_button sound_button;
		bool games_tarted;
		bool entering_highscore;

		player player;

		SDL_Surface* eye_candy;
		SDL_Surface* game_field;
		SDL_Surface* arrow;
		SDL_Surface* score;
		SDL_Surface* time;
		SDL_Surface* combos;
};

#endif
