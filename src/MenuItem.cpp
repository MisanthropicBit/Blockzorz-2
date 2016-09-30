#include "MenuItem.h"
#include "Menu.h"
#include "Graphics.h"
#include "Font.h"

//***************************************************************************************************************************
// MENU ITEM ABSTRACT BASE CLASS
//***************************************************************************************************************************

MenuItem::MenuItem(Color& normal, Color& selected) : Object()
{
	this->normal   = normal;
	this->selected = selected;
	clicked = false;
	hover   = false;
	cursor  = false;
	menu    = NULL;
}

//=========================================================================================================================

bool MenuItem::OnMouseMotion(int x, int y)
{
	return false;
}

//=========================================================================================================================

bool MenuItem::OnMouseButtonDown(int x, int y)
{
	return false;
}

//=========================================================================================================================

void MenuItem::OnMouseButtonUp()
{
}

//=========================================================================================================================

void MenuItem::OnEnter()
{
}

//=========================================================================================================================

bool MenuItem::OnRightKey()
{
	return false;
}

//=========================================================================================================================

bool MenuItem::OnLeftKey()
{
	return false;
}

//=========================================================================================================================

void MenuItem::Draw()
{
}

//=========================================================================================================================

void MenuItem::Clicked(bool flag)
{
	clicked = flag;
}

//=========================================================================================================================

void MenuItem::Select()
{
	cursor = hover = true;
}

//=========================================================================================================================

void MenuItem::Deselect()
{
	cursor = hover = false;
}

//=========================================================================================================================

bool MenuItem::IsClicked() const
{
	return clicked;
}

//=========================================================================================================================

bool MenuItem::HasHover() const
{
	return hover;
}

//=========================================================================================================================

bool MenuItem::HasCursor() const
{
	return cursor;
}

//=========================================================================================================================

string MenuItem::GetTitle() const
{
	return "";
}

//=========================================================================================================================

void MenuItem::SetMenu(Menu *menu)
{
	this->menu = menu;
}

//***************************************************************************************************************************
// BUTTON CLASS
//***************************************************************************************************************************

Button::Button(const string& title, Color& normal, Color& selected, int w, int h) : MenuItem(normal, selected)
{
	this->title = title;
	this->w = w;
	this->h = h;
}

//=========================================================================================================================

Button::~Button()
{
	menu = NULL;
}

//=========================================================================================================================

bool Button::OnMouseMotion(int x, int y)
{
	if(x >= pos.x && x <= pos.x + w && y >= pos.y && y <= pos.y + h)
	{
		hover = true;
		cursor = true;
	}
	else
	{
		if(cursor)
		{
			hover = false;
		}
		else
		{
			hover  = false;
			cursor = false;
		}
	}
	
	return hover;
}

//=========================================================================================================================

bool Button::OnMouseButtonDown(int x, int y)
{
	if(x >= pos.x && x <= pos.x + w && y >= pos.y && y <= pos.y + h)
	{
		clicked = true;
	}

	return clicked;
}

//=========================================================================================================================

void Button::OnMouseButtonUp()
{
	clicked = false;
}

//=========================================================================================================================

void Button::OnEnter()
{
	clicked = hover = true;
}

//=========================================================================================================================

bool Button::OnRightKey()
{
	return false;
}

//=========================================================================================================================

bool Button::OnLeftKey()
{
	return false;
}

//=========================================================================================================================

void Button::Draw()
{
	if(!menu) {return;}

	if(hover || cursor)
	{
		menu->GetText()->DrawHQText(title, selected, pos.x, pos.y);
	}
	else
	{
		if(menu->GetAlpha() != 0.f)
		{
			menu->GetText()->DrawTextTransparent(title, normal, menu->GetAlpha(), pos.x, pos.y);
		}
		else
		{
			menu->GetText()->DrawText(title, normal, pos.x, pos.y);
		}
	}
}

//=========================================================================================================================

string Button::GetTitle() const
{
	return title;
}

//***************************************************************************************************************************
// SELECTION CLASS
//***************************************************************************************************************************

Selection::Selection(const std::string& default, vector<string> choices, Color& normal, Color& selected) : MenuItem(normal, selected)
{
	chosen = 0;
	Choices.clear();
	Choices = choices;

	for(int i = 0; i < Choices.size(); i++)
	{
		if(Choices[i] == default)
		{
			chosen = i;
		}
	}
}

//=========================================================================================================================

void Selection::AddChoice(const std::string& choice)
{
	if(!choice.empty())
		Choices.push_back(choice);
}

//=========================================================================================================================

bool Selection::OnMouseMotion(int x, int y)
{
	int width = menu->GetText()->GetStringWidth(Choices[chosen]);
	int height = menu->GetText()->GetStringHeight(Choices[chosen]);

	if(x >= pos.x && x <= pos.x + width && y >= pos.y && y <= pos.y + height)
	{
		hover = true;
		cursor = true;
	}
	else
	{
		if(cursor)
		{
			hover = false;
		}
		else
		{
			hover  = false;
			cursor = false;
		}
	}
	
	return hover;
}

//=========================================================================================================================

void Selection::OnEnter()
{
}

//=========================================================================================================================

bool Selection::OnRightKey()
{
	if(chosen == Choices.size() - 1)
	{
		chosen = 0;
	}
	else
	{
		chosen++;
	}

	return true;
}

//=========================================================================================================================

bool Selection::OnLeftKey()
{
	if(chosen == 0)
	{
		chosen = Choices.size() - 1;
	}
	else
	{
		chosen--;
	}

	return true;
}

//=========================================================================================================================

void Selection::RenderItem()
{
	if(!menu) {return;}

	int width = menu->GetText()->GetStringWidth(Choices[chosen]);
	int height = menu->GetText()->GetStringHeight(Choices[chosen]);
	GetPos().x = menu->GetX() + menu->GetWidth()/2 - width/2;
	//GetPos().y = menu->GetY() + (menu->GetNoItems() - 1) * (menu->GetText()->GetSize() + menu->GetButtonGap());

	if(hover || cursor)
	{
		menu->GetText()->DrawHQText(Choices[chosen], selected, pos.x, pos.y);
	}
	else
	{
		if(menu->GetAlpha() != 0.f)
		{
			menu->GetText()->DrawTextTransparent(Choices[chosen], normal, menu->GetAlpha(), pos.x, pos.y);
		}
		else
		{
			menu->GetText()->DrawText(Choices[chosen], normal, pos.x, pos.y);
		}
	}
}

//=========================================================================================================================

string Selection::GetTitle() const
{
	return Choices[chosen];
}

//=========================================================================================================================