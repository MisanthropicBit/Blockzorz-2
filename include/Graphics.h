#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;

class Color;

class Graphics
{
    public:
        Graphics();

        static SDL_Surface* LoadImage(const string& file);
		static SDL_Surface* LoadImage(const string& file, Color& transparent);

        static bool DrawImage(SDL_Surface* source, float x, float y);
        static bool DrawImage(SDL_Surface* source, float x, float y, int sx, int sy, int w, int h); // Draws only part of the source image
		static void DrawHorizontalLine(int x1, int x2, int y, int thickness, Color& color);
        static void DrawVerticalLine(int y1, int y2, int x, int thickness, Color& color);

		static bool SetTransparencyColor(SDL_Surface* source, Color& color);
		static void SetTransparency(SDL_Surface* source, float alpha);
};

#endif
