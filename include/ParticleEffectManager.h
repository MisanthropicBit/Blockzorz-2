#ifndef PARTICLE_EFFECT_MANAGER_H
#define PARTICLE_EFFECT_MANAGER_H

#include <vector>
using namespace std;

// Forward declaration
class ParticleEffect;

class ParticleEffectManager
{
	public:
		ParticleEffectManager();
		~ParticleEffectManager();
		
		void AddEffect(ParticleEffect* effect);
		bool RemoveEffect(int id); // by passing an index we avoid do a linear search using a pointer
		void Update(float deltatime);
		void Draw();
		void Clear();

		int GetNoParticleEffects() const;
		int GetNoParticles() const;
		
	private:
		int particles;
		vector<ParticleEffect*> Effects;
};

#endif