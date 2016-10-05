#ifndef BLOCKZORZ2_PARTICLE_HPP
#define BLOCKZORZ2_PARTICLE_HPP

#include "object.hpp"

class particle : public object {
	public:
		particle(float alpha_decay);
		virtual void update(float delta_time) = 0;
		void reset(float x, float y);
		void reset(const object* attached_to);
		
		void set_angle(float angle);
		void set_position(float x, float y);
		void set_update_interval(float update_interval);

		void draw(SDL_Surface* shared_image);
		
	protected:
		float lifetime; // Starting alpha value
		float alpha_decay;
		float update_interval; // How often the particle is updated
		float time_left; // time left to next update
};

class exploding_particle : public particle {
	public:
		exploding_particle(float force, float alpha_decay);
		void update(float delta_time);
		
	private:
		float force;
		float angle;
};

#endif
