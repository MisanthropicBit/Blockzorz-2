#include "Button.h"
#include "Graphics.h"
#include "AudioManager.h"

//=========================================================================================================================
// Button class
//=========================================================================================================================

Button::Button()
{
	hover    = false;
	selected = false;
	caption  = "";
	image    = NULL;
	alpha    = 0.f;
}

//=========================================================================================================================

Button::~Button()
{
	if(image)
		SDL_FreeSurface(image);

	image = NULL;
}

//=========================================================================================================================

bool Button::Load(const string& caption, const string& fontfile, Color& color, int size, int x, int y)
{
	Font font("./Fonts/biocomv2.ttf", size);
	this->caption = caption;
	rect.x = x;
	rect.y = y - (font.GetHeight() - font.GetAscent() - font.GetDescent());
	image = font.LoadTextImage(caption, color);

	if(image)
	{
		rect.w = image->w;
		rect.h = font.GetHeight() + font.GetDescent();
		return true;
	}

	font.Close();
	return false;
}

//=========================================================================================================================

void Button::Draw()
{
	Graphics::DrawImage(image, rect.x, rect.y);
}

//=========================================================================================================================

void Button::SetAlpha(float alpha)
{
	if(alpha >= 0.f && alpha <= 1.f)
	{
		this->alpha = alpha;
		Graphics::SetTransparency(image, alpha);
	}
}

//=========================================================================================================================

void Button::Select()
{
	selected = true;
}

//=========================================================================================================================

void Button::Deselect()
{
	selected = false;
}

//=========================================================================================================================

bool Button::IsSelected() const
{
	return selected;
}

//=========================================================================================================================

bool Button::HasMouseHover(int mx, int my)
{
	if(mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
		return true;

	return false;
}

//=========================================================================================================================

void Button::OnMouseMove(int mx, int my)
{
	if(HasMouseHover(mx, my))
	{
		if(!IsSelected())
		{
			Select();
			SetAlpha(0.f);
			AudioManager::GetManager()->PlaySound("Click", 0);
		}
	}
	else
	{
		if(IsSelected())
		{
			Deselect();
			SetAlpha(0.8f);
		}
	}
}

//=========================================================================================================================
// AnimatedButton class
//=========================================================================================================================

AnimatedButton::AnimatedButton()
{
	frame = 0;
}

//=========================================================================================================================

AnimatedButton::~AnimatedButton()
{
}

//=========================================================================================================================

bool AnimatedButton::Load(const std::string& imagefile, int x, int y)
{
	if(!imagefile.empty())
	{
		image = Graphics::LoadImage(imagefile);

		if(!image)
			return false;

		rect.w = image->w;
		rect.h = image->h;
	}

	rect.x = x;
	rect.y = y;

	return true;
}

//=========================================================================================================================

void AnimatedButton::Draw()
{
	Graphics::DrawImage(image, rect.x, rect.y, frame * rect.w/2, 0, rect.w/2, rect.h);
}

//=========================================================================================================================

void AnimatedButton::SetFrame(int frame)
{
	this->frame = frame;
}

//=========================================================================================================================

int AnimatedButton::GetFrame() const
{
	return frame;
}

//=========================================================================================================================