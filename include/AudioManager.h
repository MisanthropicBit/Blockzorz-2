#ifndef BLOCKZORZ2_AUDIOMANAGER_HPP
#define BLOCKZORZ2_AUDIOMANAGER_HPP

/*
The AudioManager class is a singleton which handles music and sounds. It is VERY IMPORTANT to note that the member function
'LoadAudioManager' should be called before either 'LoadSounds' or 'LoadMusic', at least for it to work that is. The same
does not count for shutting down the manager: Call 'UnLoadSounds()' and 'UnLoadMusic()' as needed and the destructor will
take care of the rest. Also remember to allocate channels before using sounds ;)

- NordCoder
*/

#include "sound.hpp"
#include <fstream>
#include <map>

// Singleton
class audio_manager {
	public:
		~audio_manager();

		// Loading/Unloading
		static bool load(int frequency, Uint16 format, int channels, int chunksize);
		static bool load_sounds(const std::string& soundfile);
		static bool load_music(const std::string& musicfile);
		static void unload_sounds();
		static void unload_music();

		static audio_manager* get();

		// Sound
		void allocate_channels(int c);
		int get_allocated_channels() const;
		void play_sound(const std::string& name, int loops);
		void enable_sounds();
		void disable_sounds();
		void set_sound_volume(int volume);
		int get_sound_volume() const;
		void set_sound_volume_specific(const std::string& name, int volume);
		bool is_sound_enabled() const;
		void all_channels_fadeout(int ms);

		// Music
		void play_music(const std::string& name, int loops);
		void pause_music();
		void resume_music();
		void stop_music();
		void fadein(const std::string& name, int loops, int ms);
		void fadeout(int ms);
		void set_music_volume(int volume);
		int get_music_volume() const;
		bool is_music_playing() const;
		bool is_music_paused() const;

	private:
		audio_manager(); // The constructor is declared private because the singleton is supposed to be created by
					 	 // the provided static function

		static audio_manager* manager;
		map<string, sound*> sounds;
		map<string, Mix_Music*> music;
		int channels_allocated;
		bool sounds_enabled;
		bool music_playing;
		bool music_paused;
};

#endif
