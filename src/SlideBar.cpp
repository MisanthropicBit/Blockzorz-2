#include "SlideBar.h"
#include "Graphics.h"
#include "Color.h"

SlideBar::SlideBar()
{
	position.Zero();
	ix    = 0;
	relx  = 0;
	value = 50;
	min   = 0;
	max   = 100;
	pressed = false;
	image = NULL;
}

SlideBar::SlideBar(const string& imagefile, int x, int y, int min, int max)
{
	image = Graphics::LoadImage(imagefile);

	position.x = x;
	position.y = y;
	ix      = position.x + 50 - image->w/2;
	relx    = 0;
	value   = 50;
	this->min = min - image->w/2;
	this->max = max + image->w/2;
	pressed   = false;
}

SlideBar::~SlideBar()
{
	if(image)
		SDL_FreeSurface(image);

	image = NULL;
}

bool SlideBar::Load(const string& imagefile, int x, int y, int min, int max)
{
	image = Graphics::LoadImage(imagefile);

	position.x = x;
	position.y = y;
	ix      = position.x + 50 - image->w/2;
	value   = 50;
	this->min = min - image->w/2;
	this->max = max + image->w/2;
	pressed   = false;

	if(image)
		return true;

	return false;
}

void SlideBar::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

void SlideBar::Draw()
{
	// 0%  : 255, 0, 0
	// 100%: 124, 252, 0

	Graphics::DrawHorizontalLine(position.x + min, position.x + max, position.y + image->h/2 - 4, 8, Color(abs(124 * value/100 - 255 * (1 - value/100)), 252 * value/100, 0));
	Graphics::DrawImage(image, ix, position.y);
}

void SlideBar::SetValue(int value)
{
	if(value >= min && value <= max)
	{
		this->value = value;
		ix = position.x + this->value - image->w/2;
	}
}

void SlideBar::SetMin(int min)
{
	if(min < max)
		this->min = min;
}

void SlideBar::SetMax(int max)
{
	if(max > min)
		this->max = max;
}

int SlideBar::GetValue() const
{
	return value;
}

bool SlideBar::HasMouseHover(int mx, int my)
{
	if(mx >= ix && mx <= ix + image->w && my >= position.y && my <= position.y + image->h)
		return true;

	return false;
}

void SlideBar::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	if(pressed)
	{
		ix = mx - this->relx;

		if(ix < position.x + min)
			ix = position.x + min;
		if(ix + image->w > position.x + max)
			ix = position.x + max - image->w;

		value = ix + image->w/2 - position.x;
	}
}

void SlideBar::OnLeftButtonDown(int mx, int my)
{
	if(HasMouseHover(mx, my))
	{
		pressed = true;
		relx = mx - ix;
	}
	else
	{
		if(pressed)
			pressed = false;
	}
}

void SlideBar::OnLeftButtonUp(int mx, int my)
{
	pressed = false;
}