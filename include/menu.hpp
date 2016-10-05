#ifndef BLOCKZORZ2_MENU_HPP
#define BLOCKZORZ2_MENU_HPP

#include "font.hpp"
#include <vector>

class menu_item;

class menu {
	public:
		menu(const std::string& title = "",
             const std::string& fontfile = "",
             int fontsize = 0,
             const std::string& imagefile = "",
             int x = 0,
             int y = 0);
		~menu();

		void load(const std::string& title = "",
                  const std::string& fontfile = "",
                  int fontsize = 0,
                  const std::string& imagefile = "",
                  int x = 0,
                  int y = 0);

		void handle_event(SDL_Event& event);
		void draw();

		void add_menu_item(MenuItem* item);
		void add_button(const string& title, Color& normal, Color& select);
		void add_selection(const string& default, vector<string> choices, Color& normal, Color& select);
		void center();
		void set_button_gap(int buttongap);
		void set_alpha_unselected(float alpha);
		void set_sound(const string& soundname);

		void show();
		void hide();
		bool visible();
		int clicked();
		string item_title(int id);

		Font* get_font();
		int x() const;
		int y() const;
		int width() const;
		int height() const;
		float alpha() const;
		int button_gap() const;
		int size() const;

	private:
		int selected; // Button that is currently selected
		int x;
		int y;
		int w;
		int h;
		bool visible;
		int button_gap;
		float alpha;
		string sound_name;
		SDL_Surface* image;
		font font;

        std::vector<menu_item*> menu_items;
};

#endif
