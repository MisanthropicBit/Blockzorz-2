#include "Color.h"

//=========================================================================================================================

// static colors
Color Color::Black(0, 0, 0);
Color Color::Gray(190, 190, 190);
Color Color::White(255, 255, 255);

Color Color::Red(255, 0, 0);
Color Color::Green(0, 255, 0);
Color Color::Blue(0, 0, 255);
Color Color::Yellow(255, 255, 0);
Color Color::Magenta(255, 0, 255);
Color Color::Cyan(0, 255, 255);
Color Color::Gold(255, 215, 0);
Color Color::Silver(230, 232, 250);
Color Color::Bronze(140, 120, 83);

Color Color::DarkBlue(0, 0, 205);

//=========================================================================================================================

Color::Color(int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

//=========================================================================================================================

void Color::SetRGB(int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

//=========================================================================================================================

void Color::SetR(int r)
{
	color.r = r;
}

//=========================================================================================================================

void Color::SetG(int g)
{
	color.g = g;
}

//=========================================================================================================================

void Color::SetB(int b)
{
	color.b = b;
}

//=========================================================================================================================

Uint8& Color::GetR()
{
	return (color.r);
}

//=========================================================================================================================

Uint8& Color::GetG()
{
	return (color.g);
}

//=========================================================================================================================

Uint8& Color::GetB()
{
	return (color.b);
}

//=========================================================================================================================

Color Color::operator+ (Color& color) const
{
	Color result;
	result.GetR() = this->color.r + color.GetR();
	if(result.GetR() > 255)
		result.GetR() = 255;
	result.GetG() = this->color.g + color.GetG();
	if(result.GetG() > 255)
		result.GetG() = 255;
	result.GetB() = this->color.b + color.GetB();
	if(result.GetB() > 255)
		result.GetR() = 255;
	
	return result;
}

//=========================================================================================================================

Color Color::operator- (Color& color) const
{
	Color result;
	result.GetR() = this->color.r - color.GetR();
	if(result.GetR() < 0)
		result.GetR() = 0;
	result.GetG() = this->color.g - color.GetG();
	if(result.GetG() < 0)
		result.GetG() = 0;
	result.GetB() = this->color.b - color.GetB();
	if(result.GetB() < 0)
		result.GetB() = 0;
	
	return result;
}

//=========================================================================================================================

Color& Color::operator= (Color& color)
{
	this->color.r = color.GetR();
	this->color.g = color.GetG();
	this->color.b = color.GetB();

	return (*this);
}

//=========================================================================================================================

Color Color::operator+= (Color& color)
{
	this->SetR(this->color.r + color.GetR());
	if(this->color.r > 255)
		this->color.r = 255;
	this->SetG(this->color.g + color.GetG());
	if(this->color.g > 255)
		this->color.g = 255;
	this->SetB(this->color.b + color.GetB());
	if(this->color.b > 255)
		this->color.b = 255;
		
	return (*this);
}

//=========================================================================================================================

Color Color::operator-= (Color& color)
{
	this->SetR(this->color.r - color.GetR());
	if(this->color.r < 0)
		this->color.r = 0;
	this->SetG(this->color.g - color.GetG());
	if(this->color.g < 0)
		this->color.g = 0;
	this->SetB(this->color.b - color.GetB());
	if(this->color.b < 0)
		this->color.b = 0;
		
	return (*this);
}

//=========================================================================================================================

bool Color::operator== (Color& color) const
{
	return(this->color.r == color.GetR() && this->color.g == color.GetG() && this->color.b == color.GetB());
}

//=========================================================================================================================