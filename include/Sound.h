#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"
#include <string>
using namespace std;

class Sound
{
	public:
		Sound(const string& file);
		~Sound();

		Mix_Chunk* GetSound() const;
		bool IsValid();

	protected:
		Mix_Chunk* sound;
};

#endif