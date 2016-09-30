#include "AudioManager.h"
#include <iostream>

AudioManager* AudioManager::amanager = NULL;

//============================================================================================================================

AudioManager::AudioManager()
{
	soundsenabled = true;
	musicPlaying = false;
	musicPaused = false;
}

//============================================================================================================================

AudioManager::~AudioManager()
{
	if(amanager)
		delete amanager;
}

//============================================================================================================================

bool AudioManager::LoadAudioManager(int frequency, Uint16 format, int channels, int chunksize)
{
	amanager = NULL;
	amanager = new AudioManager();
	
	if(amanager)
	{
		Mix_OpenAudio(frequency, format, channels, chunksize);
		return true;
	}
	else
	{
		return false;
	}
}

//============================================================================================================================

bool AudioManager::LoadSounds(const string& soundfile)
{
	ifstream file;
	
	GetManager()->Sounds.clear();

	file.open(soundfile.c_str());
	string name, path = "";
	
	if(file.is_open())
	{
		while(!file.eof())
		{
			file >> name;
			file >> path;

			Sound* sound = new Sound(path);
			
			if(sound)
				GetManager()->Sounds[name] = sound;
			else
				cerr << "Error (AudioManager): Unable to load sound from file: " << path << endl;
		}

		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

//============================================================================================================================

bool AudioManager::LoadMusic(const string& musicfile)
{
	ifstream file;
	GetManager()->Music.clear();

	file.open(musicfile.c_str());
	string name, path = "";
	
	if(file.is_open())
	{
		while(!file.eof())
		{
			file >> name;
			file >> path;

			GetManager()->Music[name] = Mix_LoadMUS(path.c_str());

			if(!(GetManager()->Music[name]))
				cerr << "Error (AudioManager): Unable to load music from file: " << path << endl;
		}

		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

//============================================================================================================================

void AudioManager::UnLoadSounds()
{
    for(map<string,Sound*>::iterator Iter = GetManager()->Sounds.begin(); Iter != GetManager()->Sounds.end(); ++Iter)
    {
		delete (*Iter).second;
    }

    GetManager()->Sounds.clear();
}

//============================================================================================================================

void AudioManager::UnLoadMusic()
{
	for(map<string, Mix_Music*>::iterator Iter = GetManager()->Music.begin(); Iter != GetManager()->Music.end(); ++Iter)
    {
		Mix_FreeMusic((*Iter).second);
    }

    GetManager()->Music.clear();
}

//============================================================================================================================

AudioManager* AudioManager::GetManager()
{
	return AudioManager::amanager;
}

//============================================================================================================================

void AudioManager::AllocateChannels(int c)
{
	channelsallocated = Mix_AllocateChannels(c);
}

//============================================================================================================================

int AudioManager::GetAllocatedChannels() {return channelsallocated;}

//============================================================================================================================

void AudioManager::PlaySound(const string& name, int loops)
{
	if(!soundsenabled) {return;}

	Sound* sound = Sounds[name];

	if(channelsallocated != 0 && sound->IsValid())
	{
		Mix_PlayChannel(-1, sound->GetSound(), loops); // Plays the requested sound on the first available channel
	}
	else
	{
		printf("Unable to play sound: %s\n", name.c_str());
	}
}

//============================================================================================================================

void AudioManager::EnableSounds()
{
	soundsenabled = true;
}

//============================================================================================================================

void AudioManager::DisableSounds()
{
	soundsenabled = false;
}

//============================================================================================================================

// Set sound volume for all channels
void AudioManager::SetSoundVolume(int volume)
{
	Mix_Volume(-1, volume);
}

//============================================================================================================================

int AudioManager::GetSoundVolume()
{
	return Mix_Volume(-1, -1);
}

//============================================================================================================================

void AudioManager::SetSoundVolumeSpecific(const string& name, int volume)
{
	Mix_VolumeChunk(Sounds[name]->GetSound(), volume);
}

//============================================================================================================================

bool AudioManager::IsSoundEnabled() const
{
	return soundsenabled;
}

//============================================================================================================================

void AudioManager::AllChannelsFadeOut(int ms)
{
	Mix_FadeOutChannel(-1, ms);
}

//============================================================================================================================

void AudioManager::PlayMusic(const string& name, int loops)
{
	Mix_Music* music = Music[name];

	if(music)
	{
		Mix_PlayMusic(music, loops);
		musicPlaying = true;
		musicPaused = false;
	}
}

//============================================================================================================================

void AudioManager::PauseMusic()
{
	Mix_PauseMusic();
	musicPaused = true;
	musicPlaying = false;
}

//============================================================================================================================

void AudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
	musicPlaying = true;
	musicPaused = false;
}

//============================================================================================================================

void AudioManager::StopMusic()
{
	if(Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
		musicPaused = false;
		musicPlaying = false;
	}
}

//============================================================================================================================

void AudioManager::FadeIn(const string& name, int loops, int ms)
{
	if(ms > 0 && loops >= -1)
	{
		StopMusic();
		Mix_FadeInMusic(Music[name], loops, ms);
	}
}

//============================================================================================================================

void AudioManager::FadeOut(int ms)
{
	if(Mix_PlayingMusic() == 1 && ms > 0)
		Mix_FadeOutMusic(ms);
}

//============================================================================================================================

void AudioManager::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

//============================================================================================================================

int AudioManager::GetMusicVolume()
{
	return Mix_VolumeMusic(-1);
}

//============================================================================================================================

bool AudioManager::IsMusicPlaying()
{
	if(musicPlaying)
		return true;

	//if(Mix_PlayingMusic() == 1)
	//	return true;

	return false;
}

//===========================================================================================================================

bool AudioManager::IsMusicPaused()
{
	if(musicPaused)
		return true;

	//if(Mix_PausedMusic() == 1)
	//	return true;

	return false;
}

//===========================================================================================================================