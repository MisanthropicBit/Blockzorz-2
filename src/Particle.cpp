#include "Particle.h"
#include "Graphics.h"

//***************************************************************************************************************************
// PARTICLE BASE CLASS
//***************************************************************************************************************************

Particle::Particle(float alphadecay)
{
	this->alphadecay = alphadecay;
	lifetime = 0.f; // 0% transparency
	updateinterval = 0.f;
	speed.x = 1.f;//(rand() % 10 + 1) / 10.f;
	speed.y = 1.f;//(rand() % 10 + 1) / 10.f;
	w = 0;
	h = 0;
}

//=========================================================================================================================

void Particle::Reset(float x, float y)
{
	position.x = x;
	position.y = y;

	lifetime = 0.f;
	timeleft = updateinterval;
	dead = false;

	Graphics::SetTransparency(image, 0.f);
}

//=========================================================================================================================

// This member function has not yet been tested!
void Particle::Reset(Object* attachedTo)
{
	if(!attachedTo) {return;}
	
	position.x = attachedTo->position.x + attachedTo->w / 2 - w / 2;
	position.y = attachedTo->position.y + attachedTo->h / 2 - h / 2;

	lifetime = 0.f;
	timeleft = updateinterval;
	dead = false;

	Graphics::SetTransparency(image, 0.f);

	if(speed.IsZero())
	{
		speed.SetAngle(rand() % 360);
		speed *= (((rand() % (5 + 1)) + 5.f) / 10.f); // Scales the speed vector by a random factor between 0.5 and 1.0
	}
	else
	{
		float objectangle = attachedTo->speed.Angle();
		float lowangle = objectangle - 135;  // Image the attached object's speed is going in a 45 degree angle
		float highangle = objectangle + 135;

		speed.SetAngle(lowangle + rand() % (int)(highangle - lowangle));
		speed *= (((rand() % (5 + 1)) + 5.f) / 10.f); // Scales the speed vector by a random factor between 0.5 and 1.0
	}
}

//=========================================================================================================================

void Particle::SetXY(float x, float y)
{
	position.x = x;
	position.y = y;
}

//=========================================================================================================================

void Particle::SetAngle(float angle)
{
	speed.SetAngle(angle);
}

//=========================================================================================================================

void Particle::SetUpdateInterval(float updateinterval)
{
	this->updateinterval = updateinterval;
	timeleft = updateinterval;
}

//=========================================================================================================================

void Particle::Draw(SDL_Surface* sharedImage)
{
	Graphics::SetTransparency(sharedImage, lifetime);
	Graphics::DrawImage(sharedImage, position.x, position.y);
}

//***************************************************************************************************************************
// PARTICLE EXPLOSION
//***************************************************************************************************************************

ExplosionParticle::ExplosionParticle(float force, float alphadecay) : Particle(alphadecay)
{
	this->force = force;
	speed *= force;
}

//=========================================================================================================================

void ExplosionParticle::Update(float deltatime)
{
	timeleft -= deltatime;
	Object::Update(deltatime);

	if(timeleft <= 0) // Time to change alpha value
	{
		lifetime += alphadecay;

		if(lifetime > 1.f)
			lifetime = 1.f;

		timeleft = updateinterval;

		if(lifetime >= 1.f)
			dead = true;
	}
}

//=========================================================================================================================