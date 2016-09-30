#include "Event.h"

//=========================================================================================================================

Event::Event()
{
}

//=========================================================================================================================

Event::~Event()
{
}

//=========================================================================================================================

void Event::OnEvent(SDL_Event& event)
{
    switch(event.type)
	{
        case SDL_ACTIVEEVENT:
		{
            switch(event.active.state)
			{
                case SDL_APPMOUSEFOCUS:
				{
					if(event.active.gain)
						OnMouseFocus();
					else
						OnMouseBlur();

                    break;
                }
                case SDL_APPINPUTFOCUS:
				{
                    if(event.active.gain)
						OnInputFocus();
                    else
						OnInputBlur();

                    break;
                }
                case SDL_APPACTIVE:
				{
                    if(event.active.gain)
						OnRestore();
                    else
						OnMinimize();

                    break;
                }
            }

            break;
        }

        case SDL_KEYDOWN:
		{
            OnKeyDown(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.unicode);
            break;
        }

        case SDL_KEYUP:
		{
            OnKeyUp(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.unicode);
            break;
        }

        case SDL_MOUSEMOTION:
		{
            OnMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel, event.motion.state);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
		{
            switch(event.button.button)
			{
                case SDL_BUTTON_LEFT:
				{
                    OnLeftButtonDown(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
				{
                    OnRightButtonDown(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
				{
                    OnMiddleButtonDown(event.button.x, event.button.y);
                    break;
                }
            }

            break;
        }

        case SDL_MOUSEBUTTONUP:
		{
            switch(event.button.button)
			{
                case SDL_BUTTON_LEFT:
				{
                    OnLeftButtonUp(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
				{
                    OnRightButtonUp(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
				{
                    OnMiddleButtonUp(event.button.x, event.button.y);
                    break;
                }
            }

            break;
        }

        case SDL_QUIT:
		{
            OnExit();
            break;
        }

        case SDL_VIDEORESIZE:
		{
            OnResize(event.resize.w, event.resize.h);
            break;
        }

        case SDL_VIDEOEXPOSE:
		{
            OnExpose();
            break;
        }

        default:
            break;
    }
}

//=========================================================================================================================

void Event::OnInputFocus()
{
}

//=========================================================================================================================

void Event::OnInputBlur()
{
}

//=========================================================================================================================

void Event::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
}

//=========================================================================================================================

void Event::OnKeyUp(SDLKey key, SDLMod modifier, Uint16 unicode)
{
}

//=========================================================================================================================

void Event::OnMouseFocus()
{
}

//=========================================================================================================================

void Event::OnMouseBlur()
{
}

//=========================================================================================================================

void Event::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
}

//=========================================================================================================================

void Event::OnLeftButtonDown(int mx, int my)
{
}

//=========================================================================================================================

void Event::OnLeftButtonUp(int mx, int my)
{
}

//=========================================================================================================================

void Event::OnRightButtonDown(int mx, int my)
{
}

//=========================================================================================================================

void Event::OnRightButtonUp(int mx, int my)
{
}

//=========================================================================================================================

void Event::OnMiddleButtonDown(int mx, int my)
{
}

//=========================================================================================================================

void Event::OnMiddleButtonUp(int mx, int my)
{
}

//=========================================================================================================================

void Event::OnMinimize()
{
}

//=========================================================================================================================

void Event::OnRestore()
{
}

//=========================================================================================================================

void Event::OnResize(int w, int h)
{
}

//=========================================================================================================================

void Event::OnExpose()
{
}

//=========================================================================================================================

void Event::OnExit()
{
}

//=========================================================================================================================