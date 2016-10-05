#include "animated_object.hpp"
#include "graphics.hpp"

animated_object::animated_object() : object() {
}

animated_object::~animated_object() {
}

void animated_object::draw() {
	Graphics::draw_image(image, position.x, position.y, animation.current_frame() * 25, 0, 25, 25);
}

void animated_object::update(int dt) {
	object::update(dt);
	animation.animate(dt);
}
