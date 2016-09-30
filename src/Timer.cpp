#include "Timer.h"
#include "Font.h"

//=========================================================================================================================

Timer::Timer()
{
	started = false;
	paused = false;

	startTick = 0;
	pausedTick = 0;
	lastTick = 0;
	fpsTick = 0;
	fps = 0;
	frames = 0;
}

//============================================================================================================================

void Timer::Start()
{
	started = true;
	paused = false;
	startTick = SDL_GetTicks();//Timer::GetElapsedTime() - pausedTick;
}

//============================================================================================================================

void Timer::Pause()
{
	if(!paused)
	{
		started = false;
		paused = true;
		pausedTick = Timer::GetElapsedTime() - startTick;
	}
}

//============================================================================================================================

bool Timer::IsPaused() const
{
	return paused;
}

//============================================================================================================================

// Gets the current time elaspsed since last pause
int Timer::GetTime() const
{	
	if(started)
	{
		return Timer::GetElapsedTime() - startTick;
	}
	else
	{
		return pausedTick;
	}

	return 0;
}

//============================================================================================================================

// By calling this function in the main loop, we can calculate the fps when one second has passed.
void Timer::Update()
{
	if(SDL_GetTicks() >= (fpsTick + 1000))
	{
		fpsTick = SDL_GetTicks();
		fps = frames;
		frames = 0;
	}

	frames++;
}

//============================================================================================================================

string Timer::GetPrettyPrintTime()
{
	if((GetTime() / 1000) % 60 < 10)
	{
		return (Font::Int2String(GetTime() / 1000 / 60) + ":0" + Font::Int2String((GetTime() / 1000) % 60));
	}
	else
	{
		return (Font::Int2String(GetTime() / 1000 / 60) + ":" + Font::Int2String((GetTime() / 1000) % 60));
	}
}

//============================================================================================================================

// This function is static since it makes more sense. Elapsed time is not an individual property of each timer.
int Timer::GetElapsedTime()
{
	return SDL_GetTicks();
}

//============================================================================================================================

int Timer::GetElapsedMinutes()
{
	return (GetElapsedTime() / 1000) / 60;
}

//============================================================================================================================

int Timer::GetElapsedSeconds()
{
	return (GetElapsedTime() / 1000) % 60;
}

//============================================================================================================================

// Gets the time elapsed since this function was called
int Timer::GetDeltaTime()
{
	int deltatime = SDL_GetTicks() - lastTick; // miliseconds
	lastTick = SDL_GetTicks();

	return deltatime;
}

//============================================================================================================================

int Timer::GetFPS() const
{
	return fps;
}

//=========================================================================================================================