#ifndef BLOCKZORZ2_PLAYER_HPP
#define BLOCKZORZ2_PLAYER_HPP

#include <SDL.h>
#include <string>

class player {
	public:
		player();
		player(const std::string& file, int row, int col);
		~player();

		void load(const std::string& file, int row, int col);
		void update(int dt);
		void draw();

		void set_transparency(float alpha);
		int row();
		int column();

		void move_up();
		void move_down();
		void move_left();
		void move_right();

		void stop_moving();

	private:
		SDL_Surface* image;
		int row;
		int col;
		int movex;
		int movey;
		int keydelay;
};

#endif
