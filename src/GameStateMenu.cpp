#include "GameStateMenu.h"
#include "Graphics.h"
#include "GameStateGame.h"
#include "GameStatePopUp.h"
#include "GameStateHighscore.h"
#include "GameStateOptions.h"
#include "GameStateHowToPlay.h"
#include "GameStateManager.h"
#include "AudioManager.h"
#include "Color.h"
#include "Font.h"
#include "Screen.h"
#include "Game.h"
#include <math.h>
#include <iostream>

//=========================================================================================================================

GameStateMenu::GameStateMenu()
{
	EyeCandy   = NULL;
	Title      = NULL;
	Cursor     = NULL;
	PopUp      = NULL;
}

//=========================================================================================================================

bool GameStateMenu::Load()
{
	Font font("./Fonts/biocomv2.ttf", 60);
	EyeCandy = Graphics::LoadImage("./Graphics/Images/EyeCandy.png");
	Title    = font.LoadHQTextImage("BlockZorz 2", Color::DarkBlue);
	Cursor   = Graphics::LoadImage("./Graphics/Images/Cursor.png", Color::White);
	PopUp    = Graphics::LoadImage("./Graphics/Images/PopUp.png", Color::Magenta);

	Graphics::SetTransparency(EyeCandy, 0.5f);

	buttons[0].Load("Play", "./Fonts/biocomv2.ttf", Color::Black, 50, 180, 130);
	buttons[0].SetAlpha(0.f);
	buttons[1].Load("Highscores", "./Fonts/biocomv2.ttf", Color::Black, 50, 180, 190);
	buttons[1].SetAlpha(0.8f);
	buttons[2].Load("Options", "./Fonts/biocomv2.ttf", Color::Black, 50, 180, 250);
	buttons[2].SetAlpha(0.8f);
	buttons[3].Load("How to play", "./Fonts/biocomv2.ttf", Color::Black, 50, 180, 310);
	buttons[3].SetAlpha(0.8f);
	buttons[4].Load("Quit", "./Fonts/biocomv2.ttf", Color::Black, 50, 180, 370);
	buttons[4].SetAlpha(0.8f);

	// Set sound volume again, to ensure correct sound volume. This is because AllChannelsFadeOut(500)
	// is potentially called from the GameStateIntro when a key is pressed or the left mouse button is
	// clicked, and this sets the sound volume to 80.
	AudioManager::GetManager()->SetSoundVolume(MIX_MAX_VOLUME * Game::gamesettings.svolume / 100.f);

	titlex = Screen::GetScreen().GetWidth()/2 - font.GetStringWidth("BlockZorz 2")/2;
	selected = 0;
	cx = 145;
	cy = 130;
	offsetx = 0.f;
	offsety = 0.f;
	angle = 0.f;

	font.Close();

	if(EyeCandy && Title && Cursor) // If all images were loaded correctly, continue
	{
		if(!AudioManager::GetManager()->IsMusicPaused() && !AudioManager::GetManager()->IsMusicPlaying())
				AudioManager::GetManager()->PlayMusic("TetrisAttack", -1);

		return true;
	}

	return false;
}

//=========================================================================================================================

void GameStateMenu::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

//=========================================================================================================================

void GameStateMenu::Update(int dt)
{
	angle += 0.005f * dt;

	if(angle > 360.f)
		angle -= 360.f; // Cap the angle

	offsetx = 10.f * cos(angle);
	offsety = 10.f * sin(angle);
}

//=========================================================================================================================

void GameStateMenu::Draw()
{
	Screen::GetScreen().ClearScreenColor(Color::White);

	Graphics::DrawImage(EyeCandy, 450, 111);
	Graphics::DrawImage(Title, titlex, 20);
	Graphics::DrawImage(Cursor, cx + offsetx, cy + offsety);

	for(int i = 0; i < 5; i++)
	{
		buttons[i].Draw();
	}
}

//=========================================================================================================================

void GameStateMenu::UnLoad()
{
	SDL_FreeSurface(EyeCandy);
	SDL_FreeSurface(Title);
	SDL_FreeSurface(Cursor);
	SDL_FreeSurface(PopUp);

	EyeCandy   = NULL;
	Title      = NULL;
	Cursor     = NULL;
	PopUp      = NULL;
}

//=========================================================================================================================

void GameStateMenu::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	if(SDL_GetKeyState(NULL)[SDLK_c] && SDL_GetKeyState(NULL)[SDLK_f])
	{
		if(!Game::gamesettings.CFmodeunlocked)
		{
			Game::gamesettings.CFmodeunlocked = true;
			GameStateManager::GetManager().PushState(new GameStateModeUnlocked("Mode Unlocked!", "Captain Falcon Mode unlocked!", NULL));
		}
		else
			Game::gamesettings.CFmodeunlocked = false;	
	}

	switch(key)
	{
		case SDLK_UP:
			buttons[selected].SetAlpha(0.8f);
			if(selected == 0)
				selected = 4;
			else
				selected--;

			AudioManager::GetManager()->PlaySound("Click", 0);
			buttons[selected].SetAlpha(0.f);
			cy = 130 + selected * 60;

			break;

		case SDLK_DOWN:
			buttons[selected].SetAlpha(0.8f);
			if(selected == 4)
				selected = 0;
			else
				selected++;

			AudioManager::GetManager()->PlaySound("Click", 0);
			buttons[selected].SetAlpha(0.f);
			cy = 130 + selected * 60;

			break;

		case SDLK_RETURN:
			if(selected == 0)
				GameStateManager::GetManager().ChangeState(new GameStateGame());
			else if(selected == 1)
				GameStateManager::GetManager().ChangeState(new GameStateHighscore());
			else if(selected == 2)
				GameStateManager::GetManager().ChangeState(new GameStateOptions());
			else if(selected == 3)
				GameStateManager::GetManager().ChangeState(new GameStateHowToPlay());
			else if(selected == 4)
				GameStateManager::GetManager().PushState(new GameStatePopUp("Exit Game", "Are you sure you want to quit?", "Yes", "No", NULL));

			break;

		default:
			break;
	}
}

//=========================================================================================================================

void GameStateMenu::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	for(int i = 0; i < 5; i++)
	{
		if(buttons[i].HasMouseHover(mx, my))
		{
			if(selected != i)
			{
				buttons[selected].SetAlpha(0.8f);
				AudioManager::GetManager()->PlaySound("Click", 0);
			}

			buttons[i].SetAlpha(0.f);
			selected = i;
			cy = 130 + i * 60;
			return;
		}
		else
		{
			if(selected != i)
				buttons[i].SetAlpha(0.8f);
		}
	}
}

//=========================================================================================================================

void GameStateMenu::OnLeftButtonDown(int mx, int my)
{
	if(buttons[0].HasMouseHover(mx, my))
	{
		GameStateManager::GetManager().ChangeState(new GameStateGame());
	}
	else if(buttons[1].HasMouseHover(mx, my))
	{
		GameStateManager::GetManager().ChangeState(new GameStateHighscore());
	}
	else if(buttons[2].HasMouseHover(mx, my))
	{
		GameStateManager::GetManager().ChangeState(new GameStateOptions());
	}
	else if(buttons[3].HasMouseHover(mx, my))
	{
		GameStateManager::GetManager().ChangeState(new GameStateHowToPlay());
	}
	else if(buttons[4].HasMouseHover(mx, my))
	{
		GameStateManager::GetManager().PushState(new GameStatePopUp("Exit Game", "Are you sure you want to quit?", "Yes", "No", NULL));
	}
}

//=========================================================================================================================