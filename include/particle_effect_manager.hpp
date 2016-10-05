#ifndef BLOCKZORZ2_PARTICLE_EFFECT_MANAGER_HPP
#define BLOCKZORZ2_PARTICLE_EFFECT_MANAGER_HPP

#include <vector>

class particle_effect;

class particle_effect_manager {
	public:
		particle_effect_manager();
		~particle_effect_manager();
		
		void add_effect(particle_effect* effect);
		bool remove_effect(int id); // by passing an index we avoid do a linear search using a pointer
		void update(float deltatime);
		void draw();
		void clear();

		int size() const;
		int total_particles() const;
		
	private:
		int particles;
        std::vector<particle_effect*> effects;
};

#endif
