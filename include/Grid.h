#ifndef BLOCKZORZ2_GRID_HPP
#define BLOCKZORZ2_GRID_HPP

#include "block.hpp"
#include "particle_effect_manager.hpp"
#include "font.hpp"
#include <vector>

const int GRID_MAX_ROWS        = 14;
const int GRID_MAX_COLUMNS     = 8;
const int SPAWN_RATE           = 3000;
const int SPAWN_INTERVAL       = 30000;
const int START_SPAWN_INTERVAL = 60;
const int MAX_INCREASES        = 10;
const int SPAWN_DECAY          = 250;
const float SPAWN_DROP_SPEED   = 0.8f;
const int POINTS_PER_BLOCK     = 5;
const int COMBO_POINTS         = 20; // Old value = 7
//const int COMBO_EXTRA_POINTS = 20;

class grid {
	public:
		~grid();

		static grid& game_grid();

		void update(int dt);
		void draw();
		void spawn();
		void despawn();
		void spawn_block_at_top();
		bool is_gameover();
		bool is_spawning() const;
		
		void swap_blocks(int row, int col);
		void check_block(int row, int col);
		block_type validate_block(int row, int col);
		
		void set_width(int width);
		void set_height(int height);
		void set_block(block* block, int row, int col);
		void set_block_empty(int row, int col);
		block* get_block(int row, int col);
		int width() const;
		int height() const;
		int combos() const;
		int score() const;
		int get_rowy_coord(int row);
		int get_colx_coord(int col);
		int final_score();
		int highest_block();

		void print_grid();
		
	private:
		grid();
		static grid game_grid;

		int _width;
		int _height;
		int _combos;
		int _score;
		bool gameover;

		// In-game spawn variables
		int spawn_time;
		int spawni_nterval;
		int increased;

		// Initial spawning variables
		bool spawning;
		int spawn_time_left;
		int start_spawn_interval;
		int spawn_row;
		int spawn_col;

		block* grid[GRID_MAX_ROWS][GRID_MAX_COLUMNS];
        std::vector<Block*> spawn_list;
		void spawn_blocks(int dt);
		particle_effect_manager manager;
		font debugtext;
};

#endif
