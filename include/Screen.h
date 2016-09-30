#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"
#include <string>
using namespace std;

class Color;

// Singleton
class Screen
{
	public:
		static bool CreateScreen(int width = 640, int height = 480, int bpp = 0, Uint32 flags = SDL_ANYFORMAT);
		static void DestroyScreen();
		static Screen GetScreen();
		~Screen();

		bool SetVideoResolution(int width, int height, int bpp, Uint32 flags);
		int GetHeight();
		int GetWidth();
		int GetBitsPerPixel();
		int GetBytesPerPixel();
		Uint32 GetFlags();

		void SetCaption(const string& text);
		void SetIcon(const string& iconfile);
		string GetCaption();
		SDL_Surface* GetScreenSurface();

		void UpdateScreen(); // SDL_Flip
		void ClearScreen(); // Clears the screen with black
		void ClearScreenColor(Color& color); // Clears the screen with a color

	private:
		Screen(); // hidden constructor

		static Screen screen;
		
		SDL_Surface* screensurface;
		string caption;
};

#endif