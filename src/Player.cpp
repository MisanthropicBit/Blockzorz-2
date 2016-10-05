#include "player.hpp"
#include "graphics.hpp"
#include "color.hpp"
#include "screen.hpp"
#include "block.hpp"

player::player() {
	image     = nullptr;
	this->row = row;
	this->col = col;
	movex     = 0;
	movey     = 0;
	key_delay = 100;
}

player::player(const std::string& file, int row, int col) {
	load(file, row, col);
}

void player::load(const std::string& file, int row, int col) {
	image = nullptr;

	if (!file.empty()) {
        image = graphics::load_image(file, color::magenta);
    }

	this->row = row;
	this->col = col;
	movex     = 0;
	movey     = 0;
	key_delay = 100;
}

player::~player() {
	if (image) {
        SDL_FreeSurface(image);
    }

	image = nullptr;
}

void player::update(int dt) {
/*	keydelay -= dt;

	if(keydelay <= 0)
	{
		if(col != GRID_MAX_COLUMNS && movex > 0 || col != 0 && movex < 0)
			col += movex;

		if(row != GRID_MAX_ROWS && movey > 0 || row != 0 && movey < 0)
			row += movey;

		keydelay = 100;
	}*/
}

void player::draw() {
	graphics::draw_image(image, screen::get().width()/2 - 100 + col * BLOCK_WIDTH, row * BLOCK_HEIGHT + 50);
}

void player::set_transparency(float alpha) {
	graphics::set_transparency(image, alpha);
}

int player::row() {
	return row;
}

int player::column() {
	return col;
}

void player::start_moving_up() {
	movey = -1;
}

void player::start_moving_down() {
	movey = 1;
}

void player::start_moving_left() {
	movex = -1;
}

void player::start_moving_right() {
	movex = 1;
}

void player::stop_moving() {
	movex = 0;
	movey = 0;
}
