#ifndef BLOCKZORZ2_PARTICLE_EFFECT_HPP
#define BLOCKZORZ2_PARTICLE_EFFECT_HPP

#include <SDL.h>
#include <vector>
#include <string>
#include "vector.h"

class object;
class particle;

enum effect_type {
	EFFECT_TYPE_NONE = 0,
	EFFECT_TYPE_EXPLOSION
};

class particle_effect {
	public:
		particle_effect();
		~particle_effect();
		
		virtual void update(float deltatime) = 0;
		void draw();
		
		void set_update_interval(float low, float high);
		void show();
		void hide();
		bool is_visible() const;
		bool is_dead() const;
		void clear();
		int size() const;
		effect_type type() const;
		void set_gravity(float x, float y);
		vector& gravity();
	
	protected:
		float x;
		float y;
		bool show;
		bool dead;
		float force;
		effect_type type;
		vector gravity;

		SDL_Surface* sharedImage;
        std::vector<particle*> particles;
};

class particle_explosion_effect : public particle_effect {
	public:
		particle_explosion_effect(const std::string& file, int size, float force, float alphadecay, float x, float y);

		void update(float deltatime);
};

#endif
