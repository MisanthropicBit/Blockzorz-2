#ifndef BLOCKZORZ2_MENUITEM_HPP
#define BLOCKZORZ2_MENUITEM_HPP

#include "object.hpp"
#include "color.hpp"
#include <SDL.h>
#include <vector>

class font;
class menu;

class menu_item : public object {
	public:
		menu_item(const Color& normal, const color& selected);

		virtual bool mouse_motion(int x, int y);
		virtual bool mouse_button_down(int x, int y);
		virtual void mouse_button_up();
		virtual void enter() = 0;
		virtual bool right_key() = 0;
		virtual bool left_key() = 0;
		virtual void draw() = 0;

		void clicked(bool flag);
		void select();
		void deselect();
		//void cursor(bool flag);

		bool clicked() const;
		bool has_hover() const;
		bool has_cursor() const;
		virtual std::string title() const;

		void set_menu(menu* menu);


	protected:
		Color normal;
		Color selected;
		bool clicked;
		bool hover;
		bool cursor;

		Menu* menu; // pointer to parent
};

class button : public menu_item {
	public:
		button(const std::string& title,
               const color& normal,
               const color& selected,
               int w,
               int h);
		~button();

		bool mouse_motion(int x, int y);
		bool mouse_button_down(int x, int y);
		void mouse_button_up();
		void enter();
		bool right_key();
		bool left_key();

		void render_item();

        std::string title() const;

	protected:
        std::string title;
};

//class AnimatedButton : public MenuItem
//{
//	public:
//		Animation anim;
//
//	private:
//};

class selection : public menu_item {
	public:
		selection(const std::string& default,
                  const std::vector<string>& choices,
                  const color& normal,
                  const color& selected);

		void add_choice(const std::string& choice);
		bool mouse_motion(int x, int y);
		void enter();
		bool right_key();
		bool left_key();

		void draw();

        std::string title() const;

	private:
		int chosen;
        std::vector<string> choices;
};

#endif
