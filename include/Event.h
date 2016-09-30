#ifndef EVENT_H
#define EVENT_H

#include "SDL.h"

class Event
{
   public:
        Event();
		~Event();

        virtual void OnEvent(SDL_Event& event);

        virtual void OnInputFocus();

        virtual void OnInputBlur();

        virtual void OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode);

        virtual void OnKeyUp(SDLKey key, SDLMod modifier, Uint16 unicode);

        virtual void OnMouseFocus();

        virtual void OnMouseBlur();

        virtual void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);

        virtual void OnLeftButtonDown(int mx, int my);

        virtual void OnLeftButtonUp(int mx, int my);

        virtual void OnRightButtonDown(int mx, int my);

        virtual void OnRightButtonUp(int mx, int my);

        virtual void OnMiddleButtonDown(int mx, int my);

        virtual void OnMiddleButtonUp(int mx, int my);

        virtual void OnMinimize();

        virtual void OnRestore();

        virtual void OnResize(int w,int h);

        virtual void OnExpose();

        virtual void OnExit();
};

#endif