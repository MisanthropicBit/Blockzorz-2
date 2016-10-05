#include "menu_item.hpp"
#include "menu.hpp"
#include "graphics.hpp"
#include "font.hpp"

menu_item::menu_item(const color& normal_color, const color& selected_color) : object() {
	this->normal_color   = normal_color;
	this->selected_color = selected_color;
	clicked              = false;
	hover                = false;
	cursor               = false;
	menu                 = nullptr;
}

bool menu_item::mouse_motion(int x, int y) {
	return false;
}

bool menu_item::mouse_button_down(int x, int y) {
	return false;
}

void menu_item::mouse_button_up() {
}

void menu_item::enter() {
}

bool menu_item::left_key() {
	return false;
}

void menu_item::draw() {
}

void menu_item::set_clicked(bool flag) {
	clicked = flag;
}

void menu_item::select() {
	cursor = hover = true;
}

void menu_item::deselect() {
	cursor = hover = false;
}

bool menu_item::clicked() const {
	return clicked;
}

bool menu_item::has_hover() const {
	return hover;
}

bool menu_item::has_cursor() const {
	return cursor;
}

std::string menu_item::title() const {
	return "";
}

void menu_item::set_menu(const menu *menu) {
	this->menu = menu;
}

button::button(const std::string& title,
               const color& normal_color,
               const color& selected_color,
               int w,
               int h)
               : menu_item(normal_color, selected_color)
{
	this->title = title;
	this->w     = w;
	this->h     = h;
}

button::~button() {
	menu = nullptr;
}

bool button::mouse_motion(int x, int y) {
	if (x >= pos.x && x <= pos.x + w && y >= pos.y && y <= pos.y + h) {
		hover  = true;
		cursor = true;
	} else {
		if (cursor) {
			hover = false;
		} else {
			hover  = false;
			cursor = false;
		}
	}
	
	return hover;
}

bool button::mouse_button_down(int x, int y) {
	if (x >= pos.x && x <= pos.x + w && y >= pos.y && y <= pos.y + h) {
		clicked = true;
	}

	return clicked;
}

void button::mouse_button_up() {
	clicked = false;
}

void button::enter() {
	clicked = hover = true;
}

bool button::right_key() {
	return false;
}

bool button::left_key() {
	return false;
}

void button::draw() {
	if (!menu) {
        return;
    }

	if (hover || cursor) {
		menu->text()->draw_hq_text(title, selected, pos.x, pos.y);
	} else {
		if(menu->alpha() != 0.f) {
			menu->text()->draw_text_transparent(title, normal, menu->alpha(), pos.x, pos.y);
		} else {
			menu->text()->draw_text(title, normal, pos.x, pos.y);
		}
	}
}

std::string button::title() const {
	return title;
}

selection::selection(const std::string& default,
                     const std::vector<std::string> choices,
                     const color& normal_color,
                     const color& selected_color)
                     : MenuItem(norma_color, selecte_color) {
	chosen = 0;
	choices.clear();
	choices = choices;

	for (int i = 0; i < Choices.size(); ++i) {
		if (choices[i] == default) {
			chosen = i;
		}
	}
}

void selection::add_choice(const std::string& choice) {
	if (!choice.empty()) {
        choices.push_back(choice);
    }
}

bool selection::mouse_motion(int x, int y) {
	int width  = menu->text()->string_width(choices[chosen]);
	int height = menu->text()->string_height(choices[chosen]);

	if (x >= pos.x && x <= pos.x + width && y >= pos.y && y <= pos.y + height) {
		hover  = true;
		cursor = true;
	} else {
		if (cursor) {
			hover = false;
		} else {
			hover  = false;
			cursor = false;
		}
	}
	
	return hover;
}

void selection::enter() {
}

bool selection::right_key() {
	if(chosen == Choices.size() - 1) {
		chosen = 0;
	} else {
		chosen++;
	}

	return true;
}

bool selection::left_key() {
	if (chosen == 0) {
		chosen = choices.size() - 1;
	} else {
		--chosen;
	}

	return true;
}

void selection::render_item() {
	if (!menu) {
        return;
    }

	int width  = menu->text()->string_width(choices[chosen]);
	int height = menu->text()->string_height(choices[chosen]);

	if (hover || cursor) {
		menu->text()->draw_hq_text(choices[chosen], selected, pos.x, pos.y);
	} else {
		if (menu->alpha() != 0.f) {
			menu->text()->draw_text_transparent(choices[chosen], normal, menu->alpha(), pos.x, pos.y);
		} else {
			menu->text()->draw_text(choices[chosen], normal, pos.x, pos.y);
		}
	}
}

std::string selection::title() const {
	return choices[chosen];
}
