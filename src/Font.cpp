#include "Font.h"
#include "Graphics.h"

//=========================================================================================================================

Font::Font()
{
	font = NULL;
}

//=========================================================================================================================

Font::Font(const string& fontfile, int size)
{
	font = NULL;

	if(!fontfile.empty())
	{
		SetSize(size);
		SetFontFile(fontfile.c_str());
	}
}

//============================================================================================================================

Font::~Font()
{
}

//============================================================================================================================

void Font::Close()
{
	if(font)
		TTF_CloseFont(font);

	font = NULL;
}

//============================================================================================================================

SDL_Surface* Font::LoadTextImage(const string& text, Color& color)
{
    if(text.empty() || !font)
    {
		printf("Error: No loaded font prior to call or empty string passed to Font::LoadTextImage(const string& text, Color& color)");
		return NULL;
	}

	SDL_Color sdlcolor = {color.GetR(), color.GetG(), color.GetB()};

	return (TTF_RenderText_Solid(font, text.c_str(), sdlcolor));
}

//============================================================================================================================

SDL_Surface* Font::LoadHQTextImage(const string& text, Color& color)
{
    if(text.empty() || !font)
    {
        printf("Error: No loaded font prior to call or empty string passed to Font::LoadHQTextImage(const string& text, Color& color)");
		return NULL;
	}

	SDL_Color sdlcolor = {color.GetR(), color.GetG(), color.GetB()};

	return (TTF_RenderText_Blended(font, text.c_str(), sdlcolor));
}

//============================================================================================================================

void Font::DrawText(const string& text, Color& color, int x, int y)
{
	SDL_Surface* txtimage = LoadTextImage(text, color);
	if(!txtimage) {return;}

	Graphics::DrawImage(txtimage, x, y);
	SDL_FreeSurface(txtimage);
	txtimage = NULL;
}

//============================================================================================================================

void Font::DrawTextTransparent(const string& text, Color& color, float alpha, int x, int y)
{
	SDL_Color sdlcolor = {color.GetR(), color.GetG(), color.GetB()};
	SDL_Surface* txtimage = TTF_RenderText_Solid(font, text.c_str(), sdlcolor);
	if(!txtimage) {return;}

	Graphics::SetTransparency(txtimage, alpha);
	Graphics::DrawImage(txtimage, x, y);
	SDL_FreeSurface(txtimage);
	txtimage = NULL;
}

//============================================================================================================================

void Font::DrawText(const string& text, Color& color, int x, int y, const string& newfontfile, int size)
{
	TTF_Font* newfont = TTF_OpenFont(newfontfile.c_str(), size);
	if(!newfont)
	{
		TTF_CloseFont(newfont);
		return;
	}

	SDL_Color sdlcolor = {color.GetR(), color.GetG(), color.GetB()};

	SDL_Surface* txtimage = TTF_RenderText_Solid(newfont, text.c_str(), sdlcolor);

	if(!txtimage)
	{
		TTF_CloseFont(newfont);
		SDL_FreeSurface(txtimage);
		txtimage = NULL;
		return;
	}

	Graphics::DrawImage(txtimage, x, y);
	TTF_CloseFont(newfont);
	SDL_FreeSurface(txtimage);
	newfont = NULL;
	txtimage = NULL;
}

//============================================================================================================================

void Font::DrawHQText(const string& text, Color& color, int x, int y)
{
	if(text.empty() || !font) {return;}

	SDL_Color sdlcolor = {color.GetR(), color.GetG(), color.GetB()};

	SDL_Surface* txtimage = TTF_RenderText_Blended(font, text.c_str(), sdlcolor);
	if(!txtimage) {return;}

	Graphics::DrawImage(txtimage, x, y);
	SDL_FreeSurface(txtimage);
	txtimage = NULL;
}

//============================================================================================================================

TTF_Font* Font::GetFont() const
{
    return font;
}

//============================================================================================================================

int Font::GetSize() const
{
	return size;
}

//============================================================================================================================

int Font::GetStyle() const
{
	return (TTF_GetFontStyle(font));
}

//============================================================================================================================

int Font::GetHeight() const
{
	return (TTF_FontHeight(font));
}

//============================================================================================================================

int Font::GetAscent() const
{
	return (TTF_FontAscent(font));
}

//============================================================================================================================

int Font::GetDescent() const
{
	return (TTF_FontDescent(font));
}

//============================================================================================================================

int Font::GetRecommendedSpacing()
{
	return (TTF_FontLineSkip(font));
}

//============================================================================================================================

int Font::GetStringWidth(const string& s)
{
	int w;
	TTF_SizeText(font, s.c_str(), &w, NULL);

	return w;
}

//============================================================================================================================

int Font::GetStringHeight(const string& s)
{
	int h;
	TTF_SizeText(font, s.c_str(), NULL, &h);

	return h;
}

//============================================================================================================================

void Font::SetFontFile(const string& fontfile)
{
	if(fontfile.empty() || size < 0)
		return;

	if((font = TTF_OpenFont(fontfile.c_str(), size)) == NULL)
	{
		fprintf(stderr, "Could not open desired font (%s)\n", fontfile.c_str());
		return;
	}

	return;
}

//============================================================================================================================

void Font::SetFontFile(const string& fontfile, int size)
{
	if(fontfile.empty() || size <= 0) {return;}

	SetSize(size);
	SetFontFile(fontfile);
}

//============================================================================================================================

void Font::SetSize(int size)
{
	this->size = size;
}

//============================================================================================================================

// 'style' can be eiher TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE or TTF_STYLE_NORMAL

void Font::SetStyle(int style)
{
	TTF_SetFontStyle(font, style);
}

//============================================================================================================================

string Font::Int2String(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

//============================================================================================================================

string Font::Float2String(float f)
{
	stringstream ss;
	ss << f;
	return ss.str();
}

//============================================================================================================================

int Font::String2Int(const string& s)
{
	int i = 0;
	istringstream iss(s);

	iss >> dec >> i;

	return i;
}

//============================================================================================================================