#ifndef BLOCKZORZ2_BUTTON_HPP
#define BLOCKZORZ2_BUTTON_HPP

#include "font.h"
#include "color.h"
#include <string>

class button {
	public:
		button();
		~button();

		virtual bool load(const std::string& caption, const std::string& filename, color& color, int size, int x, int y);
		virtual void draw();

		void set_alpha(float alpha);
		void select();
		void deselect();
		bool selected() const;

		bool has_mouse_hover(int mx, int my);
		virtual void on_mouse_move(int mx, int my);

	protected:
		bool hover;
		bool selected;
		SDL_Rect rect;
		string caption;
		SDL_Surface* image;
		float alpha;
};

class animated_button : public button {
	public:
		animated_button ();
		~animated_button ();

		bool load(const std::string& filename, int x, int y);
		void draw();

		void set_frame(int frame);
		int get_frame() const;

	private:
		int frame;
};

#endif
