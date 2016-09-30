#ifndef COLOR_H
#define COLOR_H

#include "SDL.h"

class Color
{
	public:
		Color(int r = 0, int g = 0, int = 0);
		
		void SetRGB(int r, int g, int b);
		void SetR(int r);
		void SetG(int g);
		void SetB(int b);
		Uint8& GetR();
		Uint8& GetG();
		Uint8& GetB();
		
		Color operator+ (Color&) const;
		Color operator- (Color&) const;
		
		Color& operator= (Color&);
		Color operator+= (Color&);
		Color operator-= (Color&);
	
		bool operator== (Color&) const;
		
		// Grayscale
		static Color Black;
		static Color Gray;
		static Color White;

		// Standard Colors
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Yellow;
		static Color Magenta;
		static Color Cyan;
		static Color Gold;
		static Color Silver;
		static Color Bronze;

		// Dark Colors
		static Color DarkBlue;
	
	private:
		SDL_Color color;
};

#endif