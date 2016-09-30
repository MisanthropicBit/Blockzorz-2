#ifndef ANIMATED_OBJECT
#define ANIMATED_OBJECT

#include "Object.h"
#include "Animation.h"

class AnimatedObject : public Object
{
	public:
		AnimatedObject();
		~AnimatedObject();

		virtual void Draw();
		virtual void Update(int dt);

		Animation animation;
};

#endif