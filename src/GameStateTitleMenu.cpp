#include "GameStateTitleMenu.h"

GameStateTitleMenu::GameStateTitleMenu(const string& textfile) : GameState(textfile)
{
}

GameStateTitleMenu::~GameStateTitleMenu()
{
}

bool GameStateTitleMenu::Load()
{
	BackGround = NULL;
	Title      = NULL;

	BackGround = Graphics::LoadImage("");
	Title      = Graphics::LoadImage("");

	if(BackGround && Title)
		return true;

	return false;
}

void GameStateTitleMenu::HandleEvent()
{
}

void GameStateTitleMenu::Update(int dt)
{
	GameState::Update(dt);
}

void GameStateTitleMenu::Draw()
{
}

void GameStateTitleMenu::UnLoad()
{
	SDL_FreeSurface(BackGround);
	SDL_FreeSurface(Title);

	BackGround = NULL;
	Title	   = NULL;
}