#include "block.hpp"
#include "graphics.hpp"
#include "grid.hpp"
#include "screen.hpp"
#include <math.h>

block::block() {
	row        = 0;
	col        = 0;
	swapx      = 0;
	swapy      = 0;
	dropy      = 0;
	type       = BLOCK_TYPE_NOGOOD;
	isfalling  = false;
	isswapping = false;
	check      = false;
	animation.set_frame(0);
	animation.set_max_frames(2);
	animation.stop();
}

block::block(block_type type, int row, int col) : animated_object() {
	swapx      = 0;
	swapy      = 0;
	dropy      = 0;
	isfalling  = false;
	isswapping = false;
	check      = false;
	animation.set_frame(0);
	animation.set_max_frames(2);
	animation.stop();

	if(type < BLOCK_TYPE_RED || type > BLOCK_TYPE_NOGOOD) {
		this->type = BLOCK_TYPE_NOGOOD;
    } else {
		this->type = type;

		switch(type) {
			case BLOCK_TYPE_RED:
				load("./image/animations/red_block.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_BLUE:
				load("./image/animations/blue_block.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_GREEN:
				load("./images/animations/green_block.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_YELLOW:
				load("./images/animations/yellow_block.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_PURPLE:
				Load("./graphics/animations/purple_block.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			default:
				break;
		}
	}

	if (row >= 0 && row < GRID_MAX_ROWS && col >= 0 && col < GRID_MAX_COLUMNS) {
		this->row  = row;
		this->col  = col;
		position.x = 220 + col * w;
		position.y = row * h + 50;
	}
}

block::~block() {
}

void block::update(int dt) {
	object::update(dt);

	if (!grid::game_grid().is_spawning()) {
		if (is_swapping) {
			if (speed.x < 0 && position.x <= swapx || speed.x > 0 && position.x >= swapx) {
				speed.zero();
				position.x = swapx;
				is_swapping = false;

				if (!grid::game_grid().get_block(row + 1, col)) {
					fall();
                } else if (grid::game_grid().get_block(row + 1, col)) {
					if(grid::game_grid().get_block(row + 1, col)->is_falling()) {
						fall();
                    } else {
						check = true;
                    }
				}
			}
		} else if (is_falling) {
			if (position.y + h >= grid::game_grid().get_row_ycoord(GRID_MAX_ROWS)) {
                // The block reached the bottom
				isfalling  = false;
				check      = true;
				position.y = grid::game_grid().get_rowy_coord(GRID_MAX_ROWS - 1);
				speed.Zero();
			} else if (grid::game_grid().get_block(row + 1, col)) {
                // There is a block below it
				block* next_block = grid::game_grid().get_block(row + 1, col);

				if (!next_block->is_falling() && !next_block->is_dead()) {
					if (position.y + h >= next_block->position.y) {
						isfalling  = false;
						position.y = next_block->position.y - h;
						check      = true;
						speed.Zero();
					}
				}
			} else if (!grid::game_grid().get_block(row + 1, col)) {
                // There is not a block below it
				if (position.y + h > grid::game_grid().get_rowy_coord(row + 1)) {
					grid::game_grid().set_block(this, row + 1, col);
					grid::game_grid().set_block_empty(row, col);
					++row;
				}
			}
		}
	} else {
		if (position.y >= dropy) {
			position.y = dropy;
			speed.Zero();
		}
	}
}

void block::draw() {
	animated_object::draw();
}

void block::fall() {
	if(!dead) {
		speed     = vector(0, FALL_SPEED);
		is_falling = true;
	}
}

void block::kill() {
	dead = true;
}

void block::swap_left() {
	speed.x    = -SWAP_SPEED;
	swapx      = position.x - w;
	isswapping = true;
	--col;
}

void block::swap_right() {
	speed.x    = SWAP_SPEED;
	swapx      = position.x + w;
	isswapping = true;
	++col;
}

void block::check() {
	check = true;
}

bool block::needs_checking() const {
	return check;
}

void block::dont_check() {
	check = false;
}

bool block::dead() const {
	return dead;
}

bool block::falling() const {
	return isfalling;
}

bool block::swapping() const {
	return isswapping;
}

block_type block::block_type() const {
	return type;
}

int block::dropy() const {
	return dropy;
}

void block::set_dropy(int dropy) {
	this->dropy = dropy;
}

int block::row() const {
	return row;
}

int block::column() const {
	return col;
}
