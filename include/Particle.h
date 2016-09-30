#ifndef PARTICLE_H
#define PARTICLE_H

#include "Object.h"
#include <math.h>

// Abstract base class
class Particle : public Object
{
	public:
		Particle(float alphadecay);
		virtual void Update(float deltatime) = 0;
		void Reset(float x, float y);
		void Reset(Object* attachedTo);
		
		void SetAngle(float angle);
		void SetXY(float x, float y);
		void SetUpdateInterval(float updateinterval);

		void Draw(SDL_Surface* sharedImage);
		
	protected:
		float lifetime; // Starting alpha value
		float alphadecay;
		float updateinterval; // How often the particle is updated
		float timeleft; // time left to next update
};

class ExplosionParticle : public Particle
{
	public:
		ExplosionParticle(float force, float alphadecay);
		void Update(float deltatime);
		
	private:
		float force;
		float angle;
};

#endif