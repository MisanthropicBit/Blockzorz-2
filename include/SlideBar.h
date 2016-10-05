#ifndef BLOCKZORZ2_SLIDE_BAR_HPP
#define BLOCKZORZ2_SLIDE_BAR_HPP

#include <string>
#include "event.h"
#include "vector.h"

class slide_bar : public event {
	public:
		slide_bar();
		slide_bar(const std::string& image_file, int x, int y, int min, int max);
		~slide_bar();

		bool load(const std::string& imagefile, int x, int y, int min, int max);
		void on_event(SDL_Event& event);
		void draw();

		void set_value(int value);
		void set_min(int min);
		void set_max(int max);
		int get_value() const;

		bool has_mouse_hover(int mx, int my);
		void mouse_move(int mx, int my, int relx, int rely, Uint8 state);
		void left_button_down(int mx, int my);
		void left_button_up(int mx, int my);

	private:
		vector position;
		int ix; // Image x-coordinate
		int relx;
		int value;
		int min;
		int max;
		bool pressed;
		SDL_Surface* image;
};

#endif
