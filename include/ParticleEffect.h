#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include "SDL.h"

#include <vector>
#include <string>
using namespace std;

#include "Vector.h"
class Object;
class Particle;

enum EffectType
{
	EFFECT_TYPE_NONE,
	EFFECT_TYPE_EXPLOSION
};

// Abstrat base class
class ParticleEffect
{
	public:
		ParticleEffect();
		~ParticleEffect();
		
		virtual void Update(float deltatime) = 0; // pure virtual, overridden in derived classes
		void Draw();
		
		void SetUpdateInterval(float low, float high); // values in miliseconds
		void Show();
		void Hide();
		bool IsVisible() const;
		bool IsDead() const;
		void Clear();
		int GetSize() const;
		EffectType GetType() const;
		void SetGravity(float x, float y);
		Vector& GetGravity();
	
	protected:
		float x;
		float y;
		bool show;
		bool dead;
		float force;
		EffectType type;
		Vector gravity;

		SDL_Surface* sharedImage;
		vector<Particle*> Particles;
};

class ParticleExplosionEffect : public ParticleEffect
{
	public:
		ParticleExplosionEffect(const string& file, int size, float force, float alphadecay, float x, float y);

		void Update(float deltatime);
};

#endif