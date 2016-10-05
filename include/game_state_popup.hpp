#ifndef BLOCKZORZ2_GAME_STATE_POP_UP_HPP
#define BLOCKZORZ2_GAME_STATE_POP_UP_HPP

#include "game_state.hpp"
#include "button.hpp"
#include "particle_effect_manager.hpp"

class game_state_popup : public game_state {
	public:
		game_state_popup();
		game_state_popup(const std::string& caption,
                         const std::string& text,
                         const std::string& confirmtext,
                         const std::string& quittext,
                         game_state* return_state);
		~game_state_popup();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);

	private:
		button yes;
		button no;

	protected:
		SDL_Surface* fader;
		SDL_Surface* popup;
		SDL_Surface* title;
		SDL_Surface* text;

		int titlex;
		int textx;

		game_state* return_state;
};

class game_state_mode_unlocked : public game_state_popup {
	public:
		game_state_mode_unlocked ();
		game_state_mode_unlocked (const string& caption, const string& text, GameState* returnstate);
		~game_state_mode_unlocked ();

		bool load();
		void on_event(SDL_Event& event);
		void update(int dt);
		void draw();
		void unload();

		void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);

	private:
		particle_effect_manager manager;
		int particle_interval;
		button awesome;
		game_state* return_state;
};

#endif
