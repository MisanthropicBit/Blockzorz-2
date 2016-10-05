#include "audio_manager.hpp"
#include <iostream>

audio_manager* audio_manager::amanager = NULL;

audio_manager::audio_manager() {
	sounds_enabled = true;
	music_playing  = false;
	music_paused   = false;
}

audio_manager::~audio_manager() {
	if (manager) {
        delete manager;
    }
}

bool audio_manager::load(int frequency, Uint16 format, int channels, int chunksize) {
	manager = NULL;
	manager = new AudioManager();
	
	if (manager) {
		Mix_OpenAudio(frequency, format, channels, chunksize);
		return true;
	} else {
		return false;
	}
}

bool audio_manager::load_sounds(const std::string& soundfile) {
    std::ifstream file;
	
	get()->sounds.clear();
	file.open(soundfile.c_str());
    std::string name, path = "";
	
	if (file.is_open()) {
		while(!file.eof()) {
			file >> name;
			file >> path;

			sound* sound = new sound(path);
			
			if (sound) {
				get()->Sounds[name] = sound;
            } else {
                std::cerr << "Error (AudioManager): Unable to load sound from file: " << path << std::endl;
            }
		}

		file.close();
		return true;
	} else {
		return false;
	}
}

bool audio_manager::load_music(const std::string& music_file) {
    std::ifstream file;
	get()->music.clear();

	file.open(musicfile.c_str());
    std::string name, path = "";
	
	if (file.is_open()) {
		while(!file.eof()) {
			file >> name;
			file >> path;

			get()->music[name] = Mix_LoadMUS(path.c_str());

			if (!(get()->music[name])) {
                std::cerr << "Error (AudioManager): Unable to load music from file: " << path << std::endl;
            }
		}

		file.close();
		return true;
	} else {
		return false;
	}
}

void audio_manager::unload_sounds() {
    for (std::map<std::string, sound*>::iterator iter = get()->sounds.begin(); iter != get()->sounds.end(); ++iter)
    {
		delete (*iter).second;
    }

    get()->sounds.clear();
}

void audio_manager::unload_music() {
	for (std::map<std::string, Mix_Music*>::iterator iter = get()->music.begin(); iter != get()->music.end(); ++iter)
    {
		Mix_FreeMusic((*iter).second);
    }

    get()->music.clear();
}

audio_manager* audio_manager::get() {
	return AudioManager::manager;
}

void audio_manager::allocate_channels(int c) {
	channelsallocated = Mix_AllocateChannels(c);
}

int audio_manager::get_allocated_channels() const {
    return channelsallocated;
}

void audio_manager::play_sound(const std::string& name, int loops) {
	if (!soundsenabled) {
        return;
    }

	sound* sound = sounds[name];

	if (get_allocated_channels() != 0 && sound->valid()) {
        // Plays the requested sound on the first available channel
		Mix_PlayChannel(-1, sound->get_sound(), loops);
	} else {
		printf("Unable to play sound: %s\n", name.c_str());
	}
}

void audio_manager::enable_sounds() {
	sounds_enabled = true;
}

void audio_manager::disable_sounds() {
	sounds_enabled = false;
}

// Set sound volume for all channels
void audio_manager::set_sound_volume(int volume) {
	Mix_Volume(-1, volume);
}

int audio_manager::get_sound_volume() const {
	return Mix_Volume(-1, -1);
}

void audio_manager::set_sound_volume_specific(const std::string& name, int volume) {
	Mix_VolumeChunk(sounds[name]->get_sound(), volume);
}

bool audio_manager::is_sound_enabled() const {
	return sounds_enabled;
}

void audio_manager::all_channels_fadeout(int ms) {
	Mix_FadeOutChannel(-1, ms);
}

void audio_manager::PlayMusic(const std::string& name, int loops) {
	Mix_Music* music = music[name];

	if (music) {
		Mix_PlayMusic(music, loops);
		music_playing = true;
		music_paused  = false;
	}
}

void audio_manager::pause_music() {
	Mix_PauseMusic();
	musicPaused  = true;
	musicPlaying = false;
}

void audio_manager::resume_music() {
	Mix_ResumeMusic();
	musicPlaying = true;
	musicPaused  = false;
}

void audio_manager::stop_music() {
	if (Mix_PlayingMusic() == 1) {
		Mix_HaltMusic();
		musicPaused  = false;
		musicPlaying = false;
	}
}

void audio_manager::fade_in(const std::string& name, int loops, int ms) {
	if (ms > 0 && loops >= -1) {
		StopMusic();
		Mix_FadeInMusic(music[name], loops, ms);
	}
}

void AudioManager::FadeOut(int ms) {
	if (Mix_PlayingMusic() == 1 && ms > 0) {
        Mix_FadeOutMusic(ms);
    }
}

void audio_manager::set_music_volume(int volume) {
	Mix_VolumeMusic(volume);
}

int audio_manager::get_music_volume() const {
	return Mix_VolumeMusic(-1);
}

bool audio_manager::is_music_playing() const {
    return music_playing;

	//if (Mix_PlayingMusic() == 1)
	//	return true;
}

bool audio_manager::is_music_paused() const {
    return music_paused;

	//if (Mix_PausedMusic() == 1)
	//	return true;
}
