#include "Graphics.h"
#include "Color.h"
#include "Screen.h"

Graphics::Graphics() {}

//============================================================================================================================

SDL_Surface* Graphics::LoadImage(const string& file)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

	if((Surf_Temp = IMG_Load(file.c_str())) == NULL)
	{
		if(file.empty())
		{
			printf("Unable to load image: Empty string passed!\n");
		}
		else
		{
			printf("Unable to load image: %s\n", file.c_str());
		}

		return NULL;
	}

    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

//============================================================================================================================

SDL_Surface* Graphics::LoadImage(const std::string& file, Color& transparent)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

	if((Surf_Temp = IMG_Load(file.c_str())) == NULL)
	{
		if(file.empty())
		{
			printf("Unable to load image: Empty string passed!\n");
		}
		else
		{
			printf("Unable to load image: %s\n", file.c_str());
		}

		return NULL;
	}

    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);
	Graphics::SetTransparencyColor(Surf_Return, transparent);

    return Surf_Return;
}

//============================================================================================================================

bool Graphics::DrawImage(SDL_Surface* source, float x, float y)
{
    if(!source) {return false;}

	bool locked = false;
	SDL_Rect DestRect;

    DestRect.x = (Sint16)x;
    DestRect.y = (Sint16)y;

	if(SDL_MUSTLOCK(source))
	{
		SDL_LockSurface(source);
		locked = true;
	}

	SDL_BlitSurface(source, NULL, Screen::GetScreen().GetScreenSurface(), &DestRect);

	if(locked)
	{
		SDL_UnlockSurface(source);
	}

    return true;
}

//============================================================================================================================

bool Graphics::DrawImage(SDL_Surface* source, float x, float y, int sx, int sy, int w, int h)
{
    if(source == NULL) {return false;}

    SDL_Rect DestRect;

    DestRect.x = (Sint16)x;
    DestRect.y = (Sint16)y;

    SDL_Rect SourceRect;
    SourceRect.x = sx;
    SourceRect.y = sy;
    SourceRect.w = w;
    SourceRect.h = h;

    SDL_BlitSurface(source, &SourceRect, Screen::GetScreen().GetScreenSurface(), &DestRect);

    return true;
}

//============================================================================================================================

bool Graphics::SetTransparencyColor(SDL_Surface* source, Color& color)
{
	if(source == NULL) {return false;}

	SDL_SetColorKey(source, SDL_SRCCOLORKEY, SDL_MapRGB(source->format, color.GetR(), color.GetG(), color.GetB()));

	return true;
}

//============================================================================================================================

void Graphics::SetTransparency(SDL_Surface* source, float alpha)
{
	if(!source || (alpha < 0.f || alpha > 1.f))
		return;

	if(SDL_SetAlpha(source, SDL_SRCALPHA, (int)((1-alpha) * 255)) == -1) {return;}
}

//============================================================================================================================

void Graphics::DrawHorizontalLine(int x1, int x2, int y, int thickness, Color& color)
{
    SDL_Rect DestRect;

    DestRect.x = x1;
	DestRect.y = y;
    DestRect.h = thickness;
	DestRect.w = x2 - x1;

	SDL_FillRect(Screen::GetScreen().GetScreenSurface(), &DestRect, SDL_MapRGB(Screen::GetScreen().GetScreenSurface()->format, color.GetR(), color.GetG(), color.GetB()));
}

//=========================================================================================================================

void Graphics::DrawVerticalLine(int y1, int y2, int x, int thickness, Color& color)
{
    SDL_Rect DestRect;

    DestRect.x = x;
	DestRect.y = y1;
    DestRect.h = y2 - y1;
	DestRect.w = thickness;

	SDL_FillRect(Screen::GetScreen().GetScreenSurface(), &DestRect, SDL_MapRGB(Screen::GetScreen().GetScreenSurface()->format, color.GetR(), color.GetG(), color.GetB()));
}

//=========================================================================================================================