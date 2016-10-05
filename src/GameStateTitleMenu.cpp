#include "game_state_title_menu.hpp"

game_state_title_menu::game_state_title_menu(const std::string& textfile) : game_state(textfile) {
}

game_state_title_menu::~game_state_title_menu() {
}

bool game_state_title_menu::load() {
	background = graphics::load_image("");
	title      = graphics::load_image("");

	return background && title;
}

void game_state_title_menu::handle_event() {
}

void game_state_title_menu::update(int dt) {
	game_state::update(dt);
}

void game_state_title_menu::draw() {
}

void game_state_title_menu::un_load() {
	SDL_FreeSurface(background);
	SDL_FreeSurface(title);

	background = nullptr;
	title	   = nullptr;
}
