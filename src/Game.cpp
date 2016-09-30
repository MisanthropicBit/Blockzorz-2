#include "Game.h"
#include "Screen.h"
#include "SDL_ttf.h"
#include "AudioManager.h"
#include "GameStateIntro.h"
#include "GameStateManager.h"
#include "Font.h"
#include <fstream>
#include <iostream>
using namespace std;

//=========================================================================================================================

Settings Game::gamesettings;

//=========================================================================================================================

Game::Game()
{
}

//=========================================================================================================================

Game::~Game()
{
}

//=========================================================================================================================

int Game::Run()
{
	if(!Initialize()) {return -1;}

	while(GameStateManager::GetManager().IsRunning())
	{
		while(SDL_PollEvent(&event))
		{
			HandleEvent();
		}

		Think();
		Draw();
	}

	CleanUp();

	return 0;
}

//=========================================================================================================================

bool Game::Initialize()
{
	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {return false;}

	// Load TTF
	if(TTF_Init() == -1) {return false;}

	// Load the audiomanager...
	if(!AudioManager::LoadAudioManager(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1000))
		return false;
	// ...and sounds
	AudioManager::LoadSounds("./Sounds/Sounds.txt");
	AudioManager::LoadMusic("./Music/Music.txt");
	AudioManager::GetManager()->AllocateChannels(2);

	// Set settings to default values
	Game::gamesettings.mvolume = 50;
	Game::gamesettings.svolume = 50;
	Game::gamesettings.fullscreen = false;
	Game::gamesettings.CFmodeunlocked = false;

	debugtext.SetFontFile("./Fonts/biocomv2.ttf", 20);

	// Settings format:
	// MusicVolume:%
	// SoundVolume:%
	// Fullscreen:1 or 0

	ifstream file("./Data/Settings.b2s");
	string line;
	int counter = 0;
	size_t npos = 0;
	string temp;

	if(file.is_open())
	{
		getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);
		Game::gamesettings.mvolume = Font::String2Int(temp);

		getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);
		Game::gamesettings.svolume = Font::String2Int(temp);

		getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);

		if(Font::String2Int(temp) == 1)
			Game::gamesettings.fullscreen = true;
		else
			Game::gamesettings.fullscreen = false;

		getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);
		
		if(Font::String2Int(temp) == 1)
			Game::gamesettings.CFmodeunlocked = true;
		else
			Game::gamesettings.CFmodeunlocked = false;
	}
	else
	{
		cerr << "Error: Failed to load game settings" << endl
			 << "File: " << file << endl;
	}

	AudioManager::GetManager()->SetSoundVolume(MIX_MAX_VOLUME * Game::gamesettings.svolume / 100.f);
	AudioManager::GetManager()->SetMusicVolume(MIX_MAX_VOLUME * Game::gamesettings.mvolume / 100.f);

	// Create the screen
	if(Game::gamesettings.fullscreen)
	{
		if(!Screen::CreateScreen(640, 480, 0, SDL_FULLSCREEN | SDL_HWSURFACE))
			return false;
	}
	else
	{
		if(!Screen::CreateScreen(640, 480, 0, SDL_SWSURFACE))
			return false;
	}

	Screen::GetScreen().SetCaption("Blockzorz 2 (" + VERSION + ")");
	Screen::GetScreen().SetIcon("./Graphics/Images/Icon.bmp");

	GameStateManager::GetManager().ChangeState(new GameStateIntro());

	return true;
}

//=========================================================================================================================

void Game::HandleEvent()
{
	GameStateManager::GetManager().PassEvent(event);
}

//=========================================================================================================================

void Game::Think()
{
	int dt = gametimer.GetDeltaTime();
	gametimer.Update();
	GameStateManager::GetManager().UpdateStates(dt);
}

//=========================================================================================================================

void Game::Draw()
{
	GameStateManager::GetManager().DrawStates();
	Screen::GetScreen().UpdateScreen();

	debugtext.DrawHQText("FPS: " + Font::Int2String(gametimer.GetFPS()), Color::DarkBlue, 5, 5);
}

//=========================================================================================================================

void Game::CleanUp()
{
	// Save settings
	ofstream file;
	file.open("./Data/Settings.b2s", ios::trunc); // Clear last save

	if(file.is_open())
		file.close();

	file.open("./Data/Settings.b2s");

	if(file.is_open())
	{
		file << "MusicVolume:" << Font::Int2String(Game::gamesettings.mvolume) << endl;
		file << "SoundVolume:" << Font::Int2String(Game::gamesettings.svolume) << endl;

		if(Game::gamesettings.fullscreen)
			file << "Fullscreen:1" << endl;
		else
			file << "Fullscreen:0" << endl;

		if(Game::gamesettings.CFmodeunlocked)
			file << "ModeUnlocked:1";
		else
			file << "ModeUnlocked:0";

		file.close();
	}
	else
	{
		cerr << "Error: Failed to save settings" << endl;
	}

	GameStateManager::GetManager().CleanUpStates();
	AudioManager::UnLoadSounds();
	AudioManager::UnLoadMusic();
	TTF_Quit();
	Screen::DestroyScreen();

	SDL_Quit();
}

//=========================================================================================================================

// Main function
int main(int argc, char* args[])
{
	Game game;

	return game.Run();
}

//=========================================================================================================================