#include "ParticleEffectManager.h"
#include "ParticleEffect.h"

//=========================================================================================================================

ParticleEffectManager::ParticleEffectManager()
{
	particles = 0;
    Effects.clear();
}

//=========================================================================================================================

ParticleEffectManager::~ParticleEffectManager()
{
	for(int i = 0; i < Effects.size(); ++i)
		delete Effects[i];

	Effects.clear();
}

//=========================================================================================================================

void ParticleEffectManager::AddEffect(ParticleEffect* effect)
{
	if(effect)
		Effects.push_back(effect);
}

//=========================================================================================================================

bool ParticleEffectManager::RemoveEffect(int id)
{
	if(id < 0 || id > Effects.size() - 1)
		return false;

	delete Effects[id];
	Effects.erase(Effects.begin() + id);

	return true;
}

//=========================================================================================================================

void ParticleEffectManager::Update(float deltatime)
{
	for(int i = 0; i < Effects.size(); ++i)
	{
		if(!Effects[i]->IsDead())
			Effects[i]->Update(deltatime);
		else
		{
			RemoveEffect(i);
			--i;
		}
	}
}

//=========================================================================================================================

void ParticleEffectManager::Draw()
{
	for(int i = 0; i < Effects.size(); ++i)
	{
		if(Effects[i]->IsVisible())
			Effects[i]->Draw();
	}
}

//=========================================================================================================================

void ParticleEffectManager::Clear()
{
	if(Effects.empty())
		return;

	for(int i = 0; i < Effects.size(); ++i)
	{
		if(Effects[i])
			delete Effects[i];
	}

	Effects.clear();
}

//=========================================================================================================================

int ParticleEffectManager::GetNoParticleEffects() const
{
	return Effects.size();
}

//=========================================================================================================================

int ParticleEffectManager::GetNoParticles() const
{
	return particles;
}

//=========================================================================================================================