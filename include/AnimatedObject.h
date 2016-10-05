#ifndef BLOCKZORZ2_ANIMATED_OBJECT_HPP
#define BLOCKZORZ2_ANIMATED_OBJECT_HPP

#include "object.hpp"
#include "animation.hpp"

class animated_object : public object {
	public:
		animated_object();
		~animated_object();

		virtual void draw();
		virtual void update(int dt);

		animation anim;
};

#endif
