#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "SDL.h"
#include "GameState.h"
#include "GameStateIntro.h"

#include <vector>
using namespace std;

class GameStateManager
{
	public:
		~GameStateManager();

		static GameStateManager& GetManager();

		void ChangeState(GameState* gs);
		void PushState(GameState* gs);
		void PopState();
		void Quit(); // Tells the 'Game' to quit

		void PassEvent(SDL_Event& event);
		void UpdateStates(int dt);
		void DrawStates();
		void CleanUpStates();

		GameState* GetCurrentState() const;
		int GetNoStates() const;
		bool IsRunning() const;

	private:
		GameStateManager(); // hidden constructor

		static GameStateManager Gsm;

		vector<GameState*> States;
		bool Running;
};

#endif