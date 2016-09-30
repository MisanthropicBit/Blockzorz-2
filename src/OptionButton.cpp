#include "OptionButton.h"
#include "AudioManager.h"
#include "Graphics.h"

//=========================================================================================================================

OptionButton::OptionButton()
{
	current = 0;
	alpha = 0.f;
	color = Color::Black;
	selections.clear();
}

//=========================================================================================================================

OptionButton::~OptionButton()
{
	font.Close();
	selections.clear();
}

//=========================================================================================================================

bool OptionButton::Load(const string& fontfile, Color& color, int size, int x, int y)
{
	this->color = color;
	font.SetFontFile(fontfile, size);

	rect.x = x;
	rect.y = y;
	rect.w = 0;
	rect.h = font.GetHeight();

	return true;
}

//=========================================================================================================================

void OptionButton::Draw()
{
	if(current >= 0 && current <= selections.size())
		font.DrawTextTransparent(selections[current], color, alpha, rect.x, rect.y);
}

//=========================================================================================================================

void OptionButton::AddSelection(const string& selection)
{
	if(!selection.empty())
	{
		selections.push_back(selection);
		rect.w = font.GetStringWidth(selection);
	}
}

//=========================================================================================================================

bool OptionButton::SetSelection(const string& selection)
{
	for(int i = 0; i < selections.size(); i++)
	{
		if(selections[i] == selection)
		{
			current = i;
			rect.w = font.GetStringWidth(selections[current]);
			return true;
		}
	}

	return false;
}

//=========================================================================================================================

string OptionButton::GetSelection()
{
	if(!selections.empty() && current >= 0 && current <= selections.size())
		return selections[current];

	return "";
}

//=========================================================================================================================

void OptionButton::Select()
{
	selected = true;
}

//=========================================================================================================================

void OptionButton::Deselect()
{
	selected = false;
}

//=========================================================================================================================

bool OptionButton::IsSelected() const
{
	return selected;
}

//=========================================================================================================================

void OptionButton::SetAlpha(float alpha)
{
	if(alpha >= 0.f && alpha <= 1.f)
		this->alpha = alpha;
}

//=========================================================================================================================

bool OptionButton::HasMouseHover(int mx, int my)
{
	if(mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
		return true;

	return false;
}

//=========================================================================================================================

void OptionButton::OnLeftButtonDown(int mx, int my)
{
	if(HasMouseHover(mx, my))
	{
		current++;

		if(current >= selections.size())
			current = 0;

		rect.w = font.GetStringWidth(selections[current]);
	}
}

//=========================================================================================================================

void OptionButton::OnMouseMove(int mx, int my)
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