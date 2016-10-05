#include <SDL.h>
#include "animation.hpp"

animation::animation() {
    frame     = 0;
    frameinc  = 1;
    framerate = 750; // Default frame rate is 750 miliseconds
    maxframes = 0;
	timeleft  = 750;
    oscillate = false;
	animate   = true;
}

void animation::animate(int dt) {
	if (!animate) {
		return;
    }

	timeleft -= dt;
	
	if (timeleft <= 0) {
		timeleft = framerate;
		frame += frameinc;

		if (oscillate) {
			if (frame >= maxframes - 1 || frame <= 0) {
				frameinc *= -1;
            }
		} else {
			if (frame >= maxframes) {
				frame = 0;
            }
		}
	}
}

void animation::play() {
	animate = true;
}

void animation::stop() {
	animate = false;
}

void animation::set_framerate(int framerate) {
	if(framerate > 0) {
        this->framerate = framerate;
    }
}

void animation::set_frame(int frame) {
    if(frame >= 0 && frame < maxframes)
		this->frame = frame;
}

void animation::set_max_frames(int maxframes) {
	if(maxframes > 0) {
		this->maxframes = maxframes;
    }
}

void animation::oscillate() {
	oscillate = true;
}

void animation::stop_oscillate() {
	oscillate = false;
}

int animation::current_frame() const {
	return frame;
}

bool animation::is_animating() const {
	return animate;
}
