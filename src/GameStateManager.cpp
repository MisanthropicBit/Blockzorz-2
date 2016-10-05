#include "game_state_manager.hpp"
#include "screen.hpp"
#include <iostream>

game_state_manager game_state_manager::gsm;

game_state_manager::game_state_manager() {
	states.clear();
	running = true;
}

game_state_manager::~game_state_manager() {
	for (int i = 0; i < states.size(); ++i) {
		if (states[i]) {
            delete states[i];
        }
	}

	states.clear();
}

game_state_manager& game_state_manager::get() {
	return gsm;
}

void game_state_manager::change_state(game_state* gs) {
	if (gs) {
		if (!states.empty()) {
			int size = states.size();

			for (int i = 0; i < size; ++i) {
				if (states[i]) {
					states[i]->unload();
					delete states[i];
				}
			}

			states.clear();
		}

		states.push_back(gs);

		if (!states.back()->Load()) {
             // Invalid state, quit application
            Quit();
        }
	} else {
        std::cerr << "Invalid GameState passed" << std::endl;
	}
}

// Use for pop-up menus
void game_state_manager::push_state(game_state* gs) {
	if (gs) {
		states.push_back(gs);
		states.back()->Load();
	}
}

void game_state_manager::pop_state() {
	if (!states.empty()) {
		states.back()->UnLoad();
		delete states.back();
		states.pop_back();
	}
}

void game_state_manager::quit() {
	running = false;
}

game_state* game_state_manager::current_state() {
	return states.back();
}

int game_state_manager::size() const {
	return states.size();
}

bool game_state_manager::running() const {
	return running;
}

void game_state_manager::pass_event(SDL_Event& event) {
	if (!states.empty()) {
        states.back()->on_event(event);
    }
}

void game_state_manager::update_state(int dt) {
	if (states.back()) {
        states.back()->update(dt);
    }
}

void game_state_manager::draw_states() {
    for (int i = 0; i < States.size(); ++i) {
		if (states[i]) {
            states[i]->draw();
        }
	}
}

void game_state_manager::clean_up_states() {
	for (int i = 0; i < states.size(); ++i) {
		if (states[i]) {
            states[i]->unload();
        }
	}
}
