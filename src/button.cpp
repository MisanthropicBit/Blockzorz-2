#include "button.hpp"
#include "graphics.hpp"
#include "audio_manager.hpp"

button::button() {
	hover    = false;
	selected = false;
	caption  = "";
	image    = NULL;
	alpha    = 0.f;
}

button::~button() {
	if(image) {
		SDL_FreeSurface(image);
    }

	image = NULL;
}

bool button::load(const std::string& caption,
                  const std::string& fontfile,
                  const color& color,
                  int size,
                  int x,
                  int y) {
	font font("./fonts/biocomv2.ttf", size);
	this->caption = caption;
	rect.x = x;
	rect.y = y - (font.height() - font.ascent() - font.descent());
	image  = font.load_text_image(caption, color);

	if(image) {
		rect.w = image->w;
		rect.h = font.height() + font.descent();
		return true;
	}

	font.close();
	return false;
}

void button::draw()
{
	graphics::draw_image(image, rect.x, rect.y);
}

void button::set_alpha(float alpha) {
	if (alpha >= 0.f && alpha <= 1.f) {
		this->alpha = alpha;
		graphics::set_transparency(image, alpha);
	}
}

void button::select() {
	selected = true;
}

void button::deselect() {
	selected = false;
}

bool button::is_selected() const {
	return selected;
}

bool button::has_mouse_hover(int mx, int my) {
	if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {
		return true;
    }

	return false;
}

void button::mouse_move(int mx, int my) {
	if (has_mouse_hover(mx, my)) {
		if (!selected()) {
			select();
			set_alpha(0.f);
			audio_manager::get()->play_sound("click", 0);
		}
	} else {
		if (selected()) {
			deselect();
			set_alpha(0.8f);
		}
	}
}

animated_button::animated_button() {
	frame = 0;
}

animated_button::~animated_button() {
}

bool animated_button::load(const std::string& imagefile, int x, int y) {
	if(!image_file.empty()) {
		image = graphics::load_image(image_file);

		if(!image) {
			return false;
        }

		rect.w = image->w;
		rect.h = image->h;
	}

	rect.x = x;
	rect.y = y;

	return true;
}

void animated_button::draw() {
	graphics::draw_image(image, rect.x, rect.y, frame * rect.w/2, 0, rect.w/2, rect.h);
}

void animated_button::set_frame(int frame) {
	this->frame = frame;
}

int animated_button::frame() const {
	return frame;
}
