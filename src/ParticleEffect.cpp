#include "ParticleEffect.h"
#include "Particle.h"
#include "Graphics.h"

//***************************************************************************************************************************
// PARTICLE EFFECT BASE CLASS
//***************************************************************************************************************************

ParticleEffect::ParticleEffect()
{
	x = 0.f;
	y = 0.f;
	show = false;
	dead = false;
	type = EFFECT_TYPE_NONE;
	gravity.Zero();
	sharedImage = NULL;
	Particles.clear();
}

//=========================================================================================================================

ParticleEffect::~ParticleEffect()
{
	for(int i = 0; i < Particles.size(); ++i)
	{
		if(Particles[i])
			delete Particles[i];
	}

	Particles.clear();

	if(sharedImage)
		SDL_FreeSurface(sharedImage);

	sharedImage = NULL;
}

//=========================================================================================================================

void ParticleEffect::Update(float deltatime)
{
	// pure virtual
}

//=========================================================================================================================

void ParticleEffect::Draw()
{
	for(int i = 0; i < Particles.size(); ++i)
	{
		if(Particles[i] && !Particles[i]->IsDead())
			Particles[i]->Draw(sharedImage);
	}
}

//=========================================================================================================================

void ParticleEffect::SetUpdateInterval(float low, float high)
{
	for(int i = 0; i < Particles.size(); ++i)
	{
		Particles[i]->SetUpdateInterval((low + rand() % (int)(high - low + 1)));
	}
}

//=========================================================================================================================

void ParticleEffect::Show()
{
	show = true;
}

//=========================================================================================================================

void ParticleEffect::Hide()
{
	show = false;
}

//=========================================================================================================================

bool ParticleEffect::IsVisible() const
{
	return show;
}

//=========================================================================================================================

bool ParticleEffect::IsDead() const
{
	return dead;
}

//=========================================================================================================================

void ParticleEffect::Clear()
{
	if(Particles.empty())
		return;

	for(int i = 0; i < Particles.size(); ++i)
	{
		if(Particles[i])
			delete Particles[i];
	}

	Particles.clear();
}

//=========================================================================================================================

int ParticleEffect::GetSize() const
{
	return Particles.size();
}

//=========================================================================================================================

EffectType ParticleEffect::GetType() const
{
	return type;
}

//=========================================================================================================================

void ParticleEffect::SetGravity(float x, float y)
{
	gravity.x = x;
	gravity.y = y;
}

//=========================================================================================================================

Vector& ParticleEffect::GetGravity()
{
	return gravity;
}

//***************************************************************************************************************************
// PARTICLE EXPLOSION EFFECT
//***************************************************************************************************************************

ParticleExplosionEffect::ParticleExplosionEffect(const string& file, int size, float force, float alphadecay, float x, float y) : ParticleEffect()
{
	this->x = x;
	this->y = y;
	type = EFFECT_TYPE_EXPLOSION;
	sharedImage = Graphics::LoadImage(file, Color::White);

	float anglestep = 360.f / (float)size;
	
	for(int i = 0; i < size; ++i)
	{
		ExplosionParticle* ep = new ExplosionParticle(force, alphadecay);
		ep->SetAngle(i * anglestep);// + rand() % 11 - 5.f); // set angle +/- 5 for randomness
		ep->SetXY(x, y);

		if(!gravity.IsZero())
		{
			ep->acceleration.x = gravity.x;
			ep->acceleration.y = gravity.y;
		}

		Particles.push_back(ep);
	}
}

//=========================================================================================================================

void ParticleExplosionEffect::Update(float deltatime)
{
	for(vector<Particle*>::iterator it = Particles.begin(); it != Particles.end();) // No increment in this for loop!
	{
		if((*it)->IsDead())
		{
			delete (*it);
			it = Particles.erase(it);
		}
		else
		{
			if((*it))
				(*it)->Update(deltatime);
	
			++it;
		}
	}

	if(Particles.empty())
		dead = true;
}

//=========================================================================================================================