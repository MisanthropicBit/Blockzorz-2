#ifndef BLOCKZORZ2_SOUND_HPP
#define BLOCKZORZ2_SOUND_HPP

#include <SDL_mixer.h>
#include <string>

class sound {
	public:
		sound(const std::string& file);
		~sound();

		Mix_Chunk* get_sound() const;
		bool valid() const;

	protected:
		Mix_Chunk* sound;
};

#endif
