#ifndef BLOCKZORZ2_GRAPHICS_HPP
#define BLOCKZORZ2_GRAPHICS_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "color.hpp"

class graphics {
    public:
        graphics();

        static SDL_Surface* load_image(const std::string& file);
		static SDL_Surface* load_image(const std::string& file, color& transparent);

        static bool draw_image(SDL_Surface* source, float x, float y);
        static bool draw_image(SDL_Surface* source, float x, float y, int sx, int sy, int w, int h); // Draws only part of the source image
		static void draw_horizontal_line(int x1, int x2, int y, int thickness, color& color);
        static void draw_vertical_line(int y1, int y2, int x, int thickness, color& color);

		static bool set_transparency_color(SDL_Surface* source, color& color);
		static void set_transparency(SDL_Surface* source, float alpha);
};

#endif
