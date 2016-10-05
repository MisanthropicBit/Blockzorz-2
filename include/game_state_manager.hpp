#ifndef BLOCKZORZ2_GAME_STATE_MANAGER_HPP
#define BLOCKZORZ2_GAME_STATE_MANAGER_HPP

#include <SDL.h>
#include "game_state.hpp"
#include "game_state_intro.hpp"
#include <vector>

class game_state_manager {
	public:
		~game_state_manager();

		static game_state_manager& get();

		void change_state(GameState* gs);
		void push_state(GameState* gs);
		void pop_state();
		void quit();

		void pass_event(SDL_Event& event);
		void update_states(int dt);
		void draw_states();
		void cleanup_states();

		game_state* current_state() const;
		int size() const;
		bool running() const;

	private:
		game_state_manager();

		static game_state_manager manager;

        std::vector<game_state*> states;
		bool _running;
};

#endif
