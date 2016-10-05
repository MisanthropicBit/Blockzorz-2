#ifndef BLOCKZORZ2_PARTICLE_HPP
#define BLOCKZORZ2_PARTICLE_HPP

#include "object.hpp"
#include <math.h>

class particle : public object {
	public:
		particle(float alphadecay);
		virtual void update(float deltatime) = 0;
		void reset(float x, float y);
		void reset(object* attachedTo);
		
		void set_angle(float angle);
		void set_position(float x, float y);
		void set_update_interval(float updateinterval);

		void draw(SDL_Surface* sharedImage);
		
	protected:
		float lifetime; // Starting alpha value
		float alphadecay;
		float updateinterval; // How often the particle is updated
		float timeleft; // time left to next update
};

class exploding_particle : public particle {
	public:
		exploding_particle(float force, float alphadecay);
		void update(float deltatime);
		
	private:
		float force;
		float angle;
};

#endif
