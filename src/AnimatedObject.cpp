#include "AnimatedObject.h"
#include "Graphics.h"

AnimatedObject::AnimatedObject() : Object()
{
}

AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::Draw()
{
	Graphics::DrawImage(image, position.x, position.y, animation.GetCurrentFrame() * 25, 0, 25, 25);
}

void AnimatedObject::Update(int dt)
{
	Object::Update(dt);
	animation.Animate(dt);
}