#include "game_state.hpp"

game_state::game_state() {
}


game_state::~game_state() {
}

bool game_state::load() {
	return false;
}

void game_state::on_event(SDL_Event& event) {
	event::on_event(event);
}

void game_state::update(int dt) {
}

void game_state::draw() {
}

void GameState::unload() {
}
