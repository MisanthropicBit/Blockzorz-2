#ifndef BLOCKZORZ2_OPTION_BUTTON_HPP
#define BLOCKZORZ2_OPTION_BUTTON_HPP

#include "button.hpp"
#include "event.hpp"
#include "font.hpp"
#include <vector>
#include <string>

class option_button : public event {
	public:
		option_button();
		~option_button();

		bool Load(const std::string& fontfile, const color& color, int size, int x, int y);
		void draw();

		void add_selection(const std::string& selection);
		bool set_selection(const std::string& selection);
		void set_alpha(float alpha);
        std::string get_selection();

		void select();
		void deselect();
		bool is_selected() const;

		bool has_mouse_hover(int mx, int my);

		void left_button_down(int mx, int my);
		void mouse_move(int mx, int my);

	private:
		bool selected;
		int current;
		float alpha;
		SDL_Rect rect;
		color color;
		font font;
        std::vector<std::string> selections;
};

#endif
