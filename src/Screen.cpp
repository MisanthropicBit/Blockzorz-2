#include "Screen.h"
#include "Graphics.h"
#include "Color.h"

//==========================================================================================================================

Screen Screen::screen;

//==========================================================================================================================

Screen::Screen()
{
	screensurface = NULL;
}

//============================================================================================================================

Screen::~Screen()
{
}

//============================================================================================================================

bool Screen::CreateScreen(int width, int height, int bpp, Uint32 flags)
{
	if(Screen::screen.SetVideoResolution(width, height, bpp, flags))
		return true;

	return false;
}

//============================================================================================================================

void Screen::DestroyScreen()
{
	if(Screen::GetScreen().GetScreenSurface())
	{
		SDL_FreeSurface(Screen::GetScreen().GetScreenSurface());
	}
}

//============================================================================================================================

Screen Screen::GetScreen()
{
	return Screen::screen;
}

//============================================================================================================================

// Use this for resize events
bool Screen::SetVideoResolution(int width, int height, int bpp, Uint32 flags)
{
	screensurface = SDL_SetVideoMode(width, height, bpp, flags);	// SDL_Quit() takes care of deleting the video surface properly,
																	// so we can safely resize
	if(screensurface)
		return true;

	return false;
}

//============================================================================================================================

int Screen::GetHeight()
{
	return screensurface->h;
}

//============================================================================================================================

int Screen::GetWidth()
{
	return screensurface->w;
}

//============================================================================================================================

int Screen::GetBitsPerPixel()
{
	return screensurface->format->BytesPerPixel * 8;
}

//============================================================================================================================

int Screen::GetBytesPerPixel()
{
	return screensurface->format->BytesPerPixel;
}

//============================================================================================================================

Uint32 Screen::GetFlags()
{
	return screensurface->flags;
}

//============================================================================================================================

void Screen::SetCaption(const string& text)
{
	caption = text;
	SDL_WM_SetCaption(caption.c_str(), NULL);
}

//============================================================================================================================

void Screen::SetIcon(const string& iconfile)
{
	if(!iconfile.empty())
	{
		SDL_Surface* Icon = SDL_LoadBMP(iconfile.c_str()); // The IMG_Load(...) function from SDL_image does not seem to work in this case
	
		if(Icon)
			SDL_WM_SetIcon(Icon, NULL);

		SDL_FreeSurface(Icon);
		Icon = NULL;
	}
}

//============================================================================================================================

string Screen::GetCaption()
{
	return caption;
}

//============================================================================================================================

SDL_Surface* Screen::GetScreenSurface()
{
	return screensurface;
}

//============================================================================================================================

void Screen::UpdateScreen()
{
	SDL_Flip(screensurface);
}

//============================================================================================================================

void Screen::ClearScreen()
{
	SDL_FillRect(screensurface, NULL, 0); // Fills the entire screen with black
}

//============================================================================================================================

void Screen::ClearScreenColor(Color& color)
{
	SDL_FillRect(screensurface, NULL, SDL_MapRGB(screensurface->format, color.GetR(), color.GetG(), color.GetB()));
}

//============================================================================================================================