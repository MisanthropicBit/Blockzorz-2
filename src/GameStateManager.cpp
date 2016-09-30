#include "GameStateManager.h"
#include "Screen.h"
#include <iostream>

//=========================================================================================================================

GameStateManager GameStateManager::Gsm;

//=========================================================================================================================

GameStateManager::GameStateManager()
{
	States.clear();
	Running = true;
}

//=========================================================================================================================

GameStateManager::~GameStateManager()
{
	for(int i = 0; i < States.size(); i++)
	{
		if(States[i])
			delete States[i];
	}

	States.clear();
}

//=========================================================================================================================

GameStateManager& GameStateManager::GetManager()
{
	return Gsm;
}

//=========================================================================================================================

void GameStateManager::ChangeState(GameState* gs)
{
	if(gs)
	{
		if(!States.empty())
		{
			int size = States.size();

			for(int i = 0; i < size; i++)
			{
				if(States[i])
				{
					States[i]->UnLoad();
					delete States[i];
				}
			}

			States.clear();
		}

		States.push_back(gs);

		if(!States.back()->Load()) // Invalid state, quit application
			Quit();
	}
	else
	{
		cerr << "Invalid GameState passed" << endl;
	}
}

//=========================================================================================================================

void GameStateManager::PushState(GameState* gs) // Use for pop-up menus
{
	if(gs)
	{
		States.push_back(gs);
		States.back()->Load();
	}
}

//=========================================================================================================================

void GameStateManager::PopState()
{
	if(!States.empty())
	{
		States.back()->UnLoad();
		delete States.back();
		States.pop_back();
	}
}

//=========================================================================================================================

void GameStateManager::Quit()
{
	Running = false;
}

//=========================================================================================================================

GameState* GameStateManager::GetCurrentState() const
{
	return States.back();
}

//=========================================================================================================================

int GameStateManager::GetNoStates() const
{
	return States.size();
}

//=========================================================================================================================

bool GameStateManager::IsRunning() const
{
	return Running;
}

//=========================================================================================================================

void GameStateManager::PassEvent(SDL_Event& event)
{
	if(!States.empty())
		States.back()->OnEvent(event);
}

//=========================================================================================================================

void GameStateManager::UpdateStates(int dt)
{
	if(States.back())
		States.back()->Update(dt);
}

//=========================================================================================================================

void GameStateManager::DrawStates()
{
	for(int i = 0; i < States.size(); i++)
	{
		if(States[i])
			States[i]->Draw();
	}
}

//=========================================================================================================================

void GameStateManager::CleanUpStates()
{
	for(int i = 0; i < States.size(); i++)
	{
		if(States[i])
			States[i]->UnLoad();
	}
}

//=========================================================================================================================