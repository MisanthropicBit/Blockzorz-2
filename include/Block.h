#ifndef BLOCKZORZ2_BLOCK_HPP
#define BLOCKZORZ2_BLOCK_HPP

#include "animated_object.h"

const int BLOCK_WIDTH  = 25;
const int BLOCK_HEIGHT = 25;
const float SWAP_SPEED = 0.5f; // Speed at which the blocks swap
const float FALL_SPEED = 0.1f; // The speed blocks fall with when the game is in progress

enum block_type {
	BLOCK_TYPE_RED = 0,
	BLOCK_TYPE_BLUE,
	BLOCK_TYPE_GREEN,
	BLOCK_TYPE_YELLOW,
	BLOCK_TYPE_PURPLE,
	BLOCK_TYPE_NOGOOD
};

class block : public animated_object {
	public:
		block();
		block(block_type type, int row, int col);
		~block();

		virtual void update(int dt);
		virtual void draw();

		void fall();
		void kill();
		void swap_left();
		void swap_right();
		void check();
		void dont_check();
		void set_dropy(int dropy);

		bool needs_checking() const;
		bool dead() const;
		bool falling() const;
		bool swapping() const;
		block_type block_type() const;
		int get_dropy() const;
		int row() const;
		int column() const;

	protected:
		int row;
		int col;
		int swapx;
		int swapy;
		int dropy;
		block_type type;
		bool _falling;
		bool _swapping;
		bool _check;
};

#endif
