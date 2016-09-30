#include "Animation.h"
#include "SDL.h"

//=========================================================================================================================

Animation::Animation()
{
    frame     = 0;
    frameinc  = 1;
    framerate = 750; // Default frame rate is 750 miliseconds
    maxframes = 0;
	timeleft  = 750;

    oscillate = false;
	animate   = true;
}

//=========================================================================================================================

void Animation::Animate(int dt)
{
	if(!animate)
		return;

	timeleft -= dt;
	
	if(timeleft <= 0)
	{
		timeleft = framerate;

		frame += frameinc;

		if(oscillate)
		{
			if(frame >= maxframes - 1 || frame <= 0)
				frameinc *= -1;
		}
		else
		{
			if(frame >= maxframes)
				frame = 0;
		}
	}
}

//=========================================================================================================================

void Animation::Play()
{
	animate = true;
}

//=========================================================================================================================

void Animation::Stop()
{
	animate = false;
}

//=========================================================================================================================

void Animation::SetFrameRate(int framerate)
{
	if(framerate > 0)
		this->framerate = framerate;
}

//=========================================================================================================================

void Animation::SetCurrentFrame(int frame)
{
    if(frame >= 0 && frame < maxframes)
		this->frame = frame;
}

//=========================================================================================================================

void Animation::SetMaxFrames(int maxframes)
{
	if(maxframes > 0)
		this->maxframes = maxframes;
}

//=========================================================================================================================

void Animation::Oscillate()
{
	oscillate = true;
}

//=========================================================================================================================

void Animation::DontOscillate()
{
	oscillate = false;
}

//=========================================================================================================================

int Animation::GetCurrentFrame() const
{
	return frame;
}

//=========================================================================================================================

bool Animation::IsAnimating() const
{
	return animate;
}

//=========================================================================================================================