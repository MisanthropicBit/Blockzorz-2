#ifndef GAME_STATE_H
#define GAME_STATE_H

//=========================================================================================================================

#include "Event.h"

//=========================================================================================================================

class GameState : public Event // Abstract base class
{
	public:
		GameState();
		~GameState();

		virtual bool Load()                    = 0; // All
		virtual void OnEvent(SDL_Event& event) = 0; // thesefunctions
		virtual void Update(int dt)            = 0; // functions
		virtual void Draw()                    = 0; // are pure
		virtual void UnLoad()                  = 0; // virtual
};

//=========================================================================================================================

#endif