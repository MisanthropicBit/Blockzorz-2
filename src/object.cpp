#include "object.hpp"
#include "graphics.hpp"
#include "color.hpp"
#include <iostream>

object::object() {
	w     = 0;
	h     = 0;
	image = NULL;
	dead  = false;
	position.Zero();
	speed.Zero();
	acceleration.Zero();
}

object::object(const std::string& file, int w, int h) {
	w     = 0;
	h     = 0;
	image = NULL;
	dead  = false;
	position.Zero();
	speed.Zero();
	acceleration.Zero();

	load(file, w, h);
}

object::object(const std::string& file, const color& color_key, int w, int h) {
	w     = 0;
	h     = 0;
	image = NULL;
	dead  = false;
	position.Zero();
	speed.Zero();
	acceleration.Zero();

	load(file, color_key, w, h);
}

object::~object() {
	if (image) {
        SDL_FreeSurface(image);
    }

	image = nullptr;
}

void object::load(const std::string& file, int w, int h) {
	if ((image = graphics::load_image(file)) == nullptr) {
        return;
    }

	this->w = w;
	this->h = h;
}

void object::load(const std::string& file, color& color_key, int w, int h) {
	if ((image = graphics::load_image(file)) == nullptr) {
        return;
    }

	graphics::set_transparency_color(image, color_key);

	this->w = w;
	this->h = h;
}

void object::draw() {
	if (!image) {
        std::cerr << "Error (Object): Unable to draw Object. No image data available" << std::endl;
		return;
	}

	graphics::draw_image(image, position.x, position.y);
}

void object::update(int dt) {
	speed    += acceleration;
	position += speed * dt;
}

void object::set_image(SDL_Surface* new_image) {
	if (image) {
        SDL_FreeSurface(image);
    }

	image = newimage;
}

SDL_Surface* object::image() const {
	return image;
}

bool object::dead() const {
	return _dead;
}
