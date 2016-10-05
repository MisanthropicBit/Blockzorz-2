#ifndef BLOCKZORZ2_SCREEN_HPP
#define BLOCKZORZ2_SCREEN_HPP

#include <SDL.h>
#include <string>

class color;

class screen {
	public:
		static bool create_screen(int width = 640, int height = 480, int bpp = 0, Uint32 flags = SDL_ANYFORMAT);
		static void destroy_screen();
		static screen get();
		~screen();

		bool set_video_resolution(int width, int height, int bpp, Uint32 flags);
		int width();
		int height();
		int bits_per_pixel();
		int bytes_per_pixel();
		Uint32 flags();

		void set_caption(const std::string& text);
		void set_icon(const std::string& icon_file);
		string get_caption();
		SDL_Surface* get_screen_surface();

		void update_screen(); // SDL_Flip
		void clear_screen(); // Clears the screen with black
		void clear_screen_color(const color& color); // Clears the screen with a color

	private:
		screen(); // hidden constructor

		static screen screen;
		
		SDL_Surface* screen_surface;
        std::string caption;
};

#endif
