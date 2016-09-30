#include "GameStateHowToPlay.h"
#include "Font.h"
#include "Graphics.h"
#include "GameStateMenu.h"
#include "GameStateManager.h"
#include "AudioManager.h"
#include "Screen.h"
#include <math.h>

//=========================================================================================================================

GameStateHowToPlay::GameStateHowToPlay()
{
	EyeCandy = NULL;
	Title  = NULL;
	Cursor = NULL;
	Line1  = NULL;
	Line2  = NULL;
	Line3  = NULL;
	Line4  = NULL;
	Line5  = NULL;
	Line6  = NULL;
	Line7  = NULL;
	Line8  = NULL;
}

//=========================================================================================================================

GameStateHowToPlay::~GameStateHowToPlay()
{
}

//=========================================================================================================================

bool GameStateHowToPlay::Load()
{
	Font titlefont("./Fonts/biocomv2.ttf", 40);
	Font font("./Fonts/biocomv2.ttf", 20);

	EyeCandy = Graphics::LoadImage("./Graphics/Images/EyeCandy.png");
	Title = titlefont.LoadHQTextImage("How to play", Color::DarkBlue);
	Cursor   = Graphics::LoadImage("./Graphics/Images/Cursor.png", Color::White);

	Graphics::SetTransparency(EyeCandy, 0.5f);

	Line1 = font.LoadHQTextImage("- Blocks fall from the top of the screen", Color::Black);
	Line2 = font.LoadHQTextImage("- No blocks must reach above the red line", Color::Black);
	Line3 = font.LoadHQTextImage("- Press space or use the mouse to swap blocks", Color::Black);
	Line4 = font.LoadHQTextImage("- Line up 3 or more blocks in any compass direction", Color::Black);
	Line5 = font.LoadHQTextImage("  to score points", Color::Black);
	Line6 = font.LoadHQTextImage("- Connecting more than 3 blocks counts as a combo", Color::Black);
	Line7 = font.LoadHQTextImage("- Combos boost your final score", Color::Black);
	Line8 = font.LoadHQTextImage("  when the game is over", Color::Black);

	backbutton.Load("Back", "./Fonts/biocomv2.ttf", Color::Black, 30, 290, 400);
	backbutton.SetAlpha(0.8f);
	backbutton.Deselect();

	titlex = Screen::GetScreen().GetWidth()/2 - titlefont.GetStringWidth("How to play")/2;
	textx  = 50;
	texty  = 90;

	cx = 255;
	cy = 400;
	offsetx = 0.f;
	offsety = 0.f;
	angle = 0.f;

	font.Close();

	if(Title && Line1 && Line2 && Line3 && Line4 && Line5 && Line6 && Line7 && Line8)
		return true;

	return false;
}

//=========================================================================================================================

void GameStateHowToPlay::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

//=========================================================================================================================

void GameStateHowToPlay::Update(int dt)
{
	angle += 0.005f * dt;

	if(angle > 360.f)
		angle -= 360.f; // Cap the angle

	offsetx = 10.f * cos(angle);
	offsety = 10.f * sin(angle);
}

//=========================================================================================================================

void GameStateHowToPlay::Draw()
{
	Screen::GetScreen().ClearScreenColor(Color::White);

	backbutton.Draw();
	Graphics::DrawImage(EyeCandy, 450, 111);
	Graphics::DrawImage(Title, titlex, 10.f);
	Graphics::DrawImage(Cursor, cx + offsetx, cy + offsety);
	Graphics::DrawImage(Line1, textx, texty);
	Graphics::DrawImage(Line2, textx, texty + 20);
	Graphics::DrawImage(Line3, textx, texty + 20 * 2);
	Graphics::DrawImage(Line4, textx, texty + 20 * 3);
	Graphics::DrawImage(Line5, textx, texty + 20 * 4);
	Graphics::DrawImage(Line6, textx, texty + 20 * 6);
	Graphics::DrawImage(Line7, textx, texty + 20 * 7);
	Graphics::DrawImage(Line8, textx, texty + 20 * 8);
}

//=========================================================================================================================

void GameStateHowToPlay::UnLoad()
{
	SDL_FreeSurface(EyeCandy);
	SDL_FreeSurface(Title);
	SDL_FreeSurface(Cursor);
	SDL_FreeSurface(Line1);
	SDL_FreeSurface(Line2);
	SDL_FreeSurface(Line3);
	SDL_FreeSurface(Line4);
	SDL_FreeSurface(Line5);
	SDL_FreeSurface(Line6);
	SDL_FreeSurface(Line7);
	SDL_FreeSurface(Line8);

	EyeCandy = NULL;
	Title  = NULL;
	Cursor = NULL;
	Line1  = NULL;
	Line2  = NULL;
	Line3  = NULL;
	Line4  = NULL;
	Line5  = NULL;
	Line6  = NULL;
	Line7  = NULL;
	Line8  = NULL;
}

//=========================================================================================================================

void GameStateHowToPlay::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	GameStateManager::GetManager().ChangeState(new GameStateMenu());
}

//=========================================================================================================================

void GameStateHowToPlay::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	backbutton.OnMouseMove(mx, my);
}

//=========================================================================================================================

void GameStateHowToPlay::OnLeftButtonDown(int mx, int my)
{
	if(backbutton.HasMouseHover(mx, my))
	{
		GameStateManager::GetManager().ChangeState(new GameStateMenu());
	}
}

//=========================================================================================================================