#include "slide_bar.hpp"
#include "graphics.hpp"
#include "color.hpp"

slide_bar::slide_bar()
{
	position.Zero();
	ix    = 0;
	relx  = 0;
	value = 50;
	min   = 0;
	max   = 100;
	pressed = false;
	image = NULL;
}

slide_bar::slide_bar(const std::string& image_file, int x, int y, int min, int max) {
	image = graphics::load_image(image_file);

	position.x = x;
	position.y = y;
	ix         = position.x + 50 - image->w/2;
	relx       = 0;
	value      = 50;
	this->min  = min - image->w/2;
	this->max  = max + image->w/2;
	pressed    = false;
}

slide_bar::~slide_bar() {
	if (image) {
        SDL_FreeSurface(image);
    }

	image = nullptr;
}

bool slide_bar::load(const std::string& image_file, int x, int y, int min, int max) {
	image = graphics::load_image(image_file);

	position.x = x;
	position.y = y;
	ix         = position.x + 50 - image->w/2;
	value      = 50;
	this->min  = min - image->w/2;
	this->max  = max + image->w/2;
	pressed    = false;

    return image;
}

void slide_bar::on_event(SDL_Event& event) {
	event::on_event(event);
}

void slide_bar::draw() {
	// 0%  : 255, 0, 0
	// 100%: 124, 252, 0

	graphics::draw_horizontal_line(position.x + min,
                                   position.x + max,
                                   position.y + image->h/2 - 4,
                                   8,
                                   color(abs(124 * value/100 - 255 * (1 - value/100)), 252 * value/100, 0));
	graphics::draw_image(image, ix, position.y);
}

void slide_bar::set_value(int value) {
	if (value >= min && value <= max) {
		this->value = value;
		ix          = position.x + this->value - image->w/2;
	}
}

void slide_bar::set_min(int min) {
	if (min < max) {
        this->min = min;
    }
}

void slide_bar::set_max(int max) {
	if (max > min) {
        this->max = max;
    }
}

int slide_bar::value() const {
	return _value;
}

bool slide_bar::has_mouse_hover(int mx, int my) {
	return mx >= ix && mx <= ix + image->w && my >= position.y && my <= position.y + image->h;
}

void slide_bar::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
	if (pressed) {
		ix = mx - this->relx;

		if (ix < position.x + min) {
            ix = position.x + min;
        }

		if (ix + image->w > position.x + max) {
            ix = position.x + max - image->w;
        }

		value = ix + image->w/2 - position.x;
	}
}

void slide_bar::left_button_down(int mx, int my) {
	if (has_mouse_hover(mx, my)) {
		pressed = true;
		relx    = mx - ix;
	} else {
		if (pressed) {
            pressed = false;
        }
	}
}

void slide_bar::left_button_up(int mx, int my) {
	pressed = false;
}
