#include "GameStateOptions.h"
#include "GameStateMenu.h"
#include "GameStateManager.h"
#include "AudioManager.h"
#include "Graphics.h"
#include "Screen.h"
#include "Game.h"
#include <math.h>

GameStateOptions::GameStateOptions()
{
	EyeCandy = NULL;
	Title    = NULL;
	Cursor   = NULL;
	Music    = NULL;
	Sound    = NULL;
	VideoMode = NULL;
}

GameStateOptions::~GameStateOptions()
{
}

bool GameStateOptions::Load()
{
	Font titlefont("./Fonts/biocomv2.ttf", 40);
	font.SetFontFile("./Fonts/biocomv2.ttf", 20);
	EyeCandy = Graphics::LoadImage("./Graphics/Images/EyeCandy.png");
	Title    = titlefont.LoadHQTextImage("Options", Color::DarkBlue);
	Cursor   = Graphics::LoadImage("./Graphics/Images/Cursor.png", Color::White);
	Music    = font.LoadHQTextImage("Music Volume:", Color::Black);
	Sound    = font.LoadHQTextImage("Sound Volume:", Color::Black);
	VideoMode = font.LoadHQTextImage("Video Mode:", Color::Black);

	Graphics::SetTransparency(EyeCandy, 0.5f);

	backbutton.Load("Back", "./Fonts/biocomv2.ttf", Color::Black, 30, 290, 400);
	backbutton.SetAlpha(0.8f);
	backbutton.Deselect();
	musicvolume.Load("./Graphics/Images/Slider.png", 150, 110, 0, 100);
	soundvolume.Load("./Graphics/Images/Slider.png", 150, 210, 0, 100);
	videomode.Load("./Fonts/biocomv2.ttf", Color::Black, 20, 300, 300);
	videomode.SetAlpha(0.8f);
	videomode.AddSelection("Windowed Mode");
	videomode.AddSelection("Fullscreen");
	if(Game::gamesettings.fullscreen)
		videomode.SetSelection("Fullscreen");

	if(AudioManager::GetManager()->IsMusicPaused() || !AudioManager::GetManager()->IsMusicPlaying())
		mvolume = 0;
	else
		mvolume = Game::gamesettings.mvolume;

	//if(AudioManager::GetManager()->IsSoundEnabled())
		svolume = Game::gamesettings.svolume;
	//else
		//svolume = 0;

	fullscreen = Game::gamesettings.fullscreen;
	musicvolume.SetValue(mvolume);
	soundvolume.SetValue(svolume);
	selected = 0;

	titlex = Screen::GetScreen().GetWidth()/2 - titlefont.GetStringWidth("Options")/2;
	cx = 255;
	cy = 400;
	offsetx = 0.f;
	offsety = 0.f;
	angle = 0.f;

	titlefont.Close();

	if(EyeCandy && Title && Cursor && Music && Sound && VideoMode) // If all images were loaded correctly, continue
		return true;

	return false;
}

void GameStateOptions::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

void GameStateOptions::Update(int dt)
{
	angle += 0.005f * dt;

	if(angle > 360.f)
		angle -= 360.f; // Cap the angle

	offsetx = 10.f * cos(angle);
	offsety = 10.f * sin(angle);
}

void GameStateOptions::Draw()
{
	Screen::GetScreen().ClearScreenColor(Color::White);

	Graphics::DrawImage(Title, titlex, 10.f);
	Graphics::DrawImage(EyeCandy, 450, 111);

	Graphics::DrawImage(Music, 150, 80);
	font.DrawHQText(Font::Int2String(musicvolume.GetValue()) + " %", Color::Black, 380, 80);
	musicvolume.Draw();

	Graphics::DrawImage(Sound, 150, 180);
	font.DrawHQText(Font::Int2String(soundvolume.GetValue()) + " %", Color::Black, 380, 180);
	soundvolume.Draw();

	Graphics::DrawImage(VideoMode, 150, 300);
	videomode.Draw();

	backbutton.Draw();
	Graphics::DrawImage(Cursor, cx + offsetx, cy + offsety);
}

void GameStateOptions::UnLoad()
{
	Game::gamesettings.mvolume = musicvolume.GetValue();
	Game::gamesettings.svolume = soundvolume.GetValue();

	if(videomode.GetSelection() == "Windowed Mode")
		Game::gamesettings.fullscreen = false;
	else
		Game::gamesettings.fullscreen = true;

	font.Close();

	SDL_FreeSurface(EyeCandy);
	SDL_FreeSurface(Title);
	SDL_FreeSurface(Cursor);
	SDL_FreeSurface(Music);
	SDL_FreeSurface(Sound);
	SDL_FreeSurface(VideoMode);

	EyeCandy = NULL;
	Title    = NULL;
	Cursor   = NULL;
	Music    = NULL;
	Sound    = NULL;
	VideoMode = NULL;
}

void GameStateOptions::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	GameStateManager::GetManager().ChangeState(new GameStateMenu());
}

void GameStateOptions::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	musicvolume.OnMouseMove(mx, my, relx, rely, state);
	soundvolume.OnMouseMove(mx, my, relx, rely, state);
	videomode.OnMouseMove(mx, my);
	backbutton.OnMouseMove(mx, my);

	if(musicvolume.GetValue() != mvolume)
	{
		mvolume = musicvolume.GetValue();

		if(mvolume == 0)
			AudioManager::GetManager()->PauseMusic();
		else
		{
			if(AudioManager::GetManager()->IsMusicPaused())
				AudioManager::GetManager()->ResumeMusic();

			AudioManager::GetManager()->SetMusicVolume(MIX_MAX_VOLUME * mvolume / 100);
		}
	}
}

void GameStateOptions::OnLeftButtonDown(int mx, int my)
{
	musicvolume.OnLeftButtonDown(mx, my);
	soundvolume.OnLeftButtonDown(mx, my);
	videomode.OnLeftButtonDown(mx, my);

	if(videomode.GetSelection() == "Fullscreen" && !fullscreen)
	{
		Screen::GetScreen().SetVideoResolution(640, 480, 0, SDL_FULLSCREEN | SDL_SWSURFACE);
		fullscreen = true;
	}
	else if(videomode.GetSelection() == "Windowed Mode" && fullscreen)
	{
		Screen::GetScreen().SetVideoResolution(640, 480, 0, SDL_SWSURFACE);
		fullscreen = false;
	}

	if(backbutton.HasMouseHover(mx, my))
		GameStateManager::GetManager().ChangeState(new GameStateMenu());
}

void GameStateOptions::OnLeftButtonUp(int mx, int my)
{
	musicvolume.OnLeftButtonUp(mx, my);
	soundvolume.OnLeftButtonUp(mx, my);

	if(soundvolume.GetValue() != svolume)
	{
		if(svolume == 0 || !AudioManager::GetManager()->IsSoundEnabled())
			AudioManager::GetManager()->EnableSounds();

		svolume = soundvolume.GetValue();

		if(svolume == 0)
			AudioManager::GetManager()->DisableSounds();
		else
		{
			AudioManager::GetManager()->SetSoundVolume(MIX_MAX_VOLUME * svolume / 100.f);
			AudioManager::GetManager()->PlaySound("Click", 0);
		}
	}
}