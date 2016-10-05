#ifndef BLOCKZORZ2_GAME_STATE_HPP
#define BLOCKZORZ2_GAME_STATE_HPP

#include "event.hpp"

// Abstract base class 
class game_state : public event {
	public:
		game_state();
		~game_state();

		virtual bool load()                     = 0;
		virtual void on_event(SDL_Event& event) = 0;
		virtual void update(int dt)             = 0;
		virtual void draw()                     = 0;
		virtual void unload()                   = 0;
};

#endif
