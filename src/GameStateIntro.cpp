#include "GameStateIntro.h"
#include "GameStateMenu.h"

#include "GameStateManager.h"
#include "Graphics.h"
#include "AudioManager.h"
#include "Screen.h"
#include <iostream>

//=========================================================================================================================

GameStateIntro::GameStateIntro()
{
	logo  = NULL;
	fader = NULL;
}

//=========================================================================================================================

bool GameStateIntro::Load()
{
	logo     = Graphics::LoadImage("./Graphics/Images/StormGamesLogo.png");
	SDL_logo = Graphics::LoadImage("./Graphics/Images/SDLlogo.png");
	fader    = Graphics::LoadImage("./Graphics/Images/Fader.png");
	soundeffect = "RainAndThunder";
	whichlogo = 1;
	updateinterval = 40;
	Reset();

	SDL_ShowCursor(0);

	if(logo && SDL_logo && fader) // all images loaded correctly
	{
		AudioManager::GetManager()->PlaySound(soundeffect, 0);
		return true;
	}

	return false;
}

//=========================================================================================================================

void GameStateIntro::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

//=========================================================================================================================

void GameStateIntro::Update(int dt)
{
	if(istate == INTRO_STATE_FADING_IN)
	{
		fadeintime -= dt;
		if(fadeintime <= 0)
		{
			alpha += 0.05f;
			Graphics::SetTransparency(fader, alpha);
			fadeintime = updateinterval;
		}

		if(alpha >= 1.f)
		{
			alpha = 1.f;
			Graphics::SetTransparency(fader, alpha);
			istate = INTRO_STATE_DISPLAYING;
		}
	}
	else if(istate == INTRO_STATE_DISPLAYING)
	{
		displaytime -= dt;

		if(displaytime <= 0)
			istate = INTRO_STATE_FADING_OUT;
	}
	else if(istate == INTRO_STATE_FADING_OUT)
	{
		fadeouttime -= dt;
		if(fadeouttime <= 0)
		{
			alpha -= 0.05f;
			Graphics::SetTransparency(fader, alpha);
			fadeouttime = updateinterval;
		}

		if(alpha <= 0.f)
		{
			alpha = 0.f;
			Graphics::SetTransparency(fader, alpha);

			if(whichlogo == 1)
			{
				Reset();
				whichlogo++;
			}
			else
			{
				GameStateManager::GetManager().ChangeState(new GameStateMenu());
			}
		}
	}
}

//=========================================================================================================================

void GameStateIntro::Draw()
{
	if(whichlogo == 1)
	{
		Graphics::DrawImage(logo, 0, 0);
	}
	else
	{
		Graphics::DrawImage(SDL_logo, 0, 0);
	}

	Graphics::DrawImage(fader, 0, 0);
}

//=========================================================================================================================

void GameStateIntro::UnLoad()
{
	SDL_FreeSurface(logo);
	SDL_FreeSurface(SDL_logo);
	SDL_FreeSurface(fader);

	logo     = NULL;
	SDL_logo = NULL;
	fader    = NULL;

	SDL_ShowCursor(1);
}

//=========================================================================================================================

void GameStateIntro::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	if(whichlogo == 1)
	{
		AudioManager::GetManager()->AllChannelsFadeOut(500);
		whichlogo++;
		Graphics::SetTransparency(fader, 0.f);
		Reset();
	}
	else
	{
		GameStateManager::GetManager().ChangeState(new GameStateMenu());
	}
}

//=========================================================================================================================

void GameStateIntro::OnLeftButtonDown(int mx, int my)
{
	if(whichlogo == 1)
	{
		AudioManager::GetManager()->AllChannelsFadeOut(500);
		whichlogo++;
		Graphics::SetTransparency(fader, 0.f);
		Reset();
	}
	else
	{
		GameStateManager::GetManager().ChangeState(new GameStateMenu());
	}
}

//========================================================================================================================

void GameStateIntro::Reset()
{
	alpha = 0.f;
	fadeintime  = 100;
	displaytime = 3000;
	fadeouttime = 100;
	istate = INTRO_STATE_FADING_IN;
}

//========================================================================================================================