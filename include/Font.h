#ifndef FONT_H
#define FONT_H

//=========================================================================================================================

#include "SDL_ttf.h"
#include "Color.h"

#include <sstream>
#include <string>
using namespace std;

//=========================================================================================================================

class Font
{
    public:
        Font();
        Font(const string& fontfile, int size);
        ~Font();

		void Close();

		SDL_Surface* LoadTextImage(const string& text, Color& color);
		SDL_Surface* LoadHQTextImage(const string& text, Color& color);

		// Draw member functions
		void DrawText(const string& text, Color& color, int x, int y);
		void DrawTextTransparent(const string& text, Color& color, float alpha, int x, int y);
		void DrawText(const string& text, Color& color, int x, int y, const string& newfont, int size);
		void DrawHQText(const string& text, Color& color, int x, int y);

		// Getters
        TTF_Font* GetFont() const;
        int GetSize() const;
		int GetStyle() const;
		int GetHeight() const;
		int GetAscent() const;
		int GetDescent() const;
		int GetRecommendedSpacing();
		int GetStringWidth(const string& s);
		int GetStringHeight(const string& s);

	    // Setters
		void SetFontFile(const string& fontfile);
		void SetFontFile(const string& fontfile, int size);
		void SetSize(int size);
		void SetStyle(int style);
	
		// Type conversion
		static string Int2String(int i);
		static string Float2String(float f);
		static int String2Int(const string& s);

    private:
        TTF_Font* font;
        int size;
};

//=========================================================================================================================

#endif