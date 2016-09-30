#include "GameStatePopUp.h"
#include "GameStateManager.h"
#include "AudioManager.h"
#include "Graphics.h"
#include "Color.h"
#include "Font.h"
#include "Screen.h"
#include "ParticleEffect.h"

GameStatePopUp::GameStatePopUp()
{
	Fader = NULL;
	PopUp = NULL;
	Title = NULL;
	Text  = NULL;
}

GameStatePopUp::GameStatePopUp(const string& caption, const string& text, const string& confirmtext, const string& quittext, GameState* returnstate)
{
	Fader = NULL;
	PopUp = NULL;
	Title = NULL;
	Text  = NULL;

	Font titlefont("./Fonts/biocomv2.ttf", 30);
	Font textfont("./Fonts/biocomv2.ttf", 20);

	Title = titlefont.LoadHQTextImage(caption, Color::DarkBlue);
	Text  = textfont.LoadHQTextImage(text, Color::Black);

	Yes.Load(confirmtext, "./Fonts/biocomv2.ttf", Color::Black, 25, 200 - textfont.GetStringWidth(confirmtext)/2, 280);
	No.Load(quittext, "./Fonts/biocomv2.ttf", Color::Black, 25, 400 - textfont.GetStringWidth(quittext)/2, 280);
	Yes.SetAlpha(0.8f);
	No.SetAlpha(0.8f);

	this->returnstate = returnstate;

	titlex = Screen::GetScreen().GetWidth()/2 - titlefont.GetStringWidth(caption)/2;
	textx  = Screen::GetScreen().GetWidth()/2 - textfont.GetStringWidth(text)/2;

	titlefont.Close();
	textfont.Close();
}

GameStatePopUp::~GameStatePopUp()
{
}

bool GameStatePopUp::Load()
{
	Fader = Graphics::LoadImage("./Graphics/Images/Fader.png");
	PopUp = Graphics::LoadImage("./Graphics/Images/PopUp.png", Color::Magenta);
	Graphics::SetTransparency(Fader, 0.5f);

	if(Fader && PopUp && Title && Text)
		return true;

	return false;
}

void GameStatePopUp::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

void GameStatePopUp::Update(int dt)
{
}

void GameStatePopUp::Draw()
{
	Graphics::DrawImage(Fader, 0, 0);
	Graphics::DrawImage(PopUp, 120, 140);
	Graphics::DrawImage(Title, titlex, 150);
	Graphics::DrawImage(Text, 140, 230);

	Yes.Draw();
	No.Draw();
}

void GameStatePopUp::UnLoad()
{
	returnstate = NULL;

	SDL_FreeSurface(Fader);
	SDL_FreeSurface(PopUp);
	SDL_FreeSurface(Title);
	SDL_FreeSurface(Text);

	Fader = NULL;
	PopUp = NULL;
	Title = NULL;
	Text  = NULL;
}

void GameStatePopUp::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	if(key == SDLK_y || key == SDLK_RETURN)
	{
		if(returnstate)
		{
			GameStateManager::GetManager().ChangeState(returnstate);
		}
		else
		{
			delete returnstate;
			GameStateManager::GetManager().Quit();
		}
	}
	else if(key == SDLK_n || key == SDLK_BACKSPACE || key == SDLK_ESCAPE)
	{
		delete returnstate;
		GameStateManager::GetManager().PopState();
	}
}

void GameStatePopUp::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	Yes.OnMouseMove(mx, my);
	No.OnMouseMove(mx, my);
}

void GameStatePopUp::OnLeftButtonDown(int mx, int my)
{
	if(Yes.HasMouseHover(mx, my))
	{
		if(returnstate)
			GameStateManager::GetManager().ChangeState(returnstate);
		else
		{
			delete returnstate;
			GameStateManager::GetManager().Quit();
		}
	}
	else if(No.HasMouseHover(mx, my))
	{
		delete returnstate;
		GameStateManager::GetManager().PopState();
	}
}

GameStateModeUnlocked::GameStateModeUnlocked() : GameStatePopUp()
{
	particleinterval = 400;
}

GameStateModeUnlocked::GameStateModeUnlocked(const string& caption, const string& text, GameState* returnstate) : GameStatePopUp()
{
	Font titlefont("./Fonts/biocomv2.ttf", 30);
	Font textfont("./Fonts/biocomv2.ttf", 20);

	Title = titlefont.LoadHQTextImage(caption, Color::DarkBlue);
	Text  = textfont.LoadHQTextImage(text, Color::Black);

	awesome.Load("Yeeees!", "./Fonts/biocomv2.ttf", Color::Gold, 25, 250, 280);
	awesome.SetAlpha(0.5f);

	this->returnstate = returnstate;
	particleinterval = 400;

	titlex = Screen::GetScreen().GetWidth()/2 - titlefont.GetStringWidth(caption)/2;
	textx  = Screen::GetScreen().GetWidth()/2 - textfont.GetStringWidth(text)/2;

	titlefont.Close();
	textfont.Close();
}

GameStateModeUnlocked::~GameStateModeUnlocked()
{
}

bool GameStateModeUnlocked::Load()
{
	AudioManager::GetManager()->PlaySound("Screech", 0);
	AudioManager::GetManager()->PlaySound("Moves", 0);

	return GameStatePopUp::Load();
}

void GameStateModeUnlocked::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

void GameStateModeUnlocked::Update(int dt)
{
	particleinterval -= dt;
	peManager.Update(dt);

	if(particleinterval <= 0)
	{
		particleinterval = 400;

		ParticleExplosionEffect* pex = new ParticleExplosionEffect("./Graphics/Images/Cursor.png", 8, 0.1f, 0.1f, rand() % 641, rand() % 481);
		pex->SetUpdateInterval(40, 80);
		pex->Show();
		peManager.AddEffect(pex);
	}
}

void GameStateModeUnlocked::Draw()
{
	Graphics::DrawImage(Fader, 0, 0);
	Graphics::DrawImage(PopUp, 120, 140);
	Graphics::DrawImage(Title, titlex, 150);
	Graphics::DrawImage(Text, 140, 230);

	awesome.Draw();
	peManager.Draw();
}

void GameStateModeUnlocked::UnLoad()
{
	GameStatePopUp::UnLoad();
}

void GameStateModeUnlocked::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	if(key == SDLK_RETURN)
		GameStateManager::GetManager().PopState();
}

void GameStateModeUnlocked::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	if(awesome.HasMouseHover(mx, my))
	{
		if(!awesome.IsSelected())
		{
			awesome.Select();
			awesome.SetAlpha(0.f);
			AudioManager::GetManager()->PlaySound("Click", 0);
		}
	}
	else
	{
		if(awesome.IsSelected())
		{
			awesome.Deselect();
			awesome.SetAlpha(0.8f);
		}
	}
}

void GameStateModeUnlocked::OnLeftButtonDown(int mx, int my)
{
	if(awesome.HasMouseHover(mx, my))
		GameStateManager::GetManager().PopState();
}