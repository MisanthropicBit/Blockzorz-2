#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"
#include <cstdio>
#include <string>
using namespace std;

class Timer
{
	public:
		Timer();
		
		void Update();

		void Start();
		void Pause();

		bool IsPaused() const;

		int GetTime() const;
		int GetDeltaTime();
		int GetLastTick() const;
		int GetFPS() const;

		string GetPrettyPrintTime();

		static int GetElapsedTime();
		static int GetElapsedMinutes();
		static int GetElapsedSeconds();

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