#ifndef BLOCKZORZ2_TIMER_HPP
#define BLOCKZORZ2_TIMER_HPP

#include <SDL.h>
#include <cstdio>
#include <string>

class timer {
	public:
		timer();
		
		void update();

		void start();
		void pause();

		bool paused() const;

		int get_time() const;
		int get_delta_time();
		int get_last_tick() const;
		int get_fps() const;

		string get_pretty_print_time();

		static int elapsed_time();
		static int elapsed_minutes();
		static int elapsed_seconds();

	protected:
		bool started;
		bool paused;
		int startTick;
		int pausedTick;
		int lastTick;
		int fpsTick;
		int fps;
		int frames;
};

#endif
