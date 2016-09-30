#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

/*
The AudioManager class is a singleton which handles music and sounds. It is VERY IMPORTANT to note that the member function
'LoadAudioManager' should be called before either 'LoadSounds' or 'LoadMusic', at least for it to work that is. The same
does not count for shutting down the manager: Call 'UnLoadSounds()' and 'UnLoadMusic()' as needed and the destructor will
take care of the rest. Also remember to allocate channels before using sounds ;)

- NordCoder
*/


#include "Sound.h"
#include <fstream>
#include <map>

// Singleton
class AudioManager
{
	public:
		~AudioManager();

		// Loading/Unloading
		static bool LoadAudioManager(int frequency, Uint16 format, int channels, int chunksize);
		static bool LoadSounds(const string& soundfile);
		static bool LoadMusic(const string& musicfile);
		static void UnLoadSounds();
		static void UnLoadMusic();

		static AudioManager* GetManager();

		// Sound
		void AllocateChannels(int c);
		int GetAllocatedChannels();
		void PlaySound(const string& name, int loops);
		void EnableSounds();
		void DisableSounds();
		void SetSoundVolume(int volume);
		int GetSoundVolume();
		void SetSoundVolumeSpecific(const string& name, int volume);
		bool IsSoundEnabled() const;
		void AllChannelsFadeOut(int ms);

		// Music
		void PlayMusic(const string& name, int loops);
		void PauseMusic();
		void ResumeMusic();
		void StopMusic();
		void FadeIn(const string& name, int loops, int ms);
		void FadeOut(int ms);
		void SetMusicVolume(int volume);
		int GetMusicVolume();
		bool IsMusicPlaying();
		bool IsMusicPaused();

	private:
		AudioManager(); // The constructor is declared private because the singleton is supposed to be created by
						// the provided static function

		static AudioManager* amanager;
		map<string, Sound*> Sounds;
		map<string, Mix_Music*> Music;
		int channelsallocated;
		bool soundsenabled;
		bool musicPlaying;
		bool musicPaused;
};

#endif