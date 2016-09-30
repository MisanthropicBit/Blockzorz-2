#include "Menu.h"
#include "MenuItem.h"
#include "Graphics.h"
#include "Screen.h"
#include "AudioManager.h"

//============================================================================================================================

Menu::Menu(const string& title, const string& fontfile, int fontsize, const string& imagefile, int x, int y)
{
	Load(title, fontfile, fontsize, imagefile, x, y);
	visible = false;
	buttongap = 5;
	alpha = 0.f;
	selected = 0;
	soundname = "";
}

//============================================================================================================================

Menu::~Menu()
{
	for(int i = 0; i < MenuItems.size(); i++)
	{
		delete MenuItems[i];
	}

	MenuItems.clear();
}

//============================================================================================================================

void Menu::Load(const string& title, const string& fontfile, int fontsize, const string& imagefile, int x, int y)
{
	this->x = x;
	this->y = y;

	if(image)
	{
		SDL_FreeSurface(image);
		image = NULL;
	}

	image = Graphics::LoadImage(imagefile);
	font.SetFont(fontfile, fontsize);
	MenuItems.clear();
}

//============================================================================================================================

void Menu::HandleEvent(SDL_Event& event)
{
	if(!IsVisible() || MenuItems.empty()) {return;} // Menu not visible or no items to evaluate, so no need to handle events

	if(event.type == SDL_KEYDOWN) // Handle keyboard
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP:
				MenuItems[selected]->Deselect();
			
				if(selected == 0)
				{
					selected = MenuItems.size() - 1;
				}
				else
				{
					selected -= 1;
				}

				if(!soundname.empty()) {AudioManager::GetManager()->PlaySound(soundname, 0);}
				MenuItems[selected]->Select();

				break;

			case SDLK_DOWN:
				MenuItems[selected]->Deselect();
			
				if(selected == MenuItems.size() - 1)
				{
					selected = 0;
				}
				else
				{
					selected += 1;
				}

				if(!soundname.empty()) {AudioManager::GetManager()->PlaySound(soundname, 0);}
				MenuItems[selected]->Select();
				break;

			case SDLK_RIGHT:
				if(MenuItems[selected]->OnRightKey()) {AudioManager::GetManager()->PlaySound(soundname, 0);}
				break;

			case SDLK_LEFT:
				if(MenuItems[selected]->OnLeftKey()) {AudioManager::GetManager()->PlaySound(soundname, 0);}
				break;

			case SDLK_RETURN:
				MenuItems[selected]->OnEnter();
				break;

			default:
				break;
		}
	}
	else if(event.type == SDL_KEYUP)
	{
		MenuItems[selected]->Clicked(false);
	}
	else if(event.type == SDL_MOUSEMOTION) // Handle mouse movement
	{
		int ShiftHover = -1;

		for(int i = 0; i < MenuItems.size(); i++)
		{
			if(MenuItems[i]->OnMouseMotion(event.motion.x, event.motion.y))
			{
				ShiftHover = i;
			}
		}

		if(ShiftHover >= 0)
		{
			if(!soundname.empty() && (ShiftHover != selected))
			{
				AudioManager::GetManager()->PlaySound(soundname, 0);

			}
			MenuItems[selected]->Deselect();
			selected = ShiftHover;
			MenuItems[selected]->Select();
		}
	}
	else if(event.type == SDL_MOUSEBUTTONDOWN) // Handle mouse button
	{
		for(int i = 0; i < MenuItems.size(); i++)
		{
			MenuItems[i]->OnMouseButtonDown(event.button.x, event.button.y);
		}
	}
	else if(event.type == SDL_MOUSEBUTTONUP)
	{
		for(int i = 0; i < MenuItems.size(); i++)
		{
			MenuItems[i]->OnMouseButtonUp();
		}
	}
}

//============================================================================================================================

void Menu::Draw()
{
	if(!IsVisible()) {return;}

	Graphics::DrawImage(image, x - w/2, y - (GetNoItems() * buttongap) / 2);

	for(int i = 0; i < MenuItems.size(); i++)
	{
		MenuItems[i]->Draw();
	}
}

//============================================================================================================================

void Menu::AddMenuItem(MenuItem* item)
{
	item->SetMenu(this);
	MenuItems.push_back(item);

	if(MenuItems.size() == 1) // If this is the first button, select it.
		button->Select();
}

//============================================================================================================================

void Menu::AddButton(const string& title, Color& normal, Color& selected)
{
	Button* button = new Button(title, normal, selected, text.GetStringWidth(title), text.GetStringHeight(title));
	button->GetPos().x = x + w/2 - button->GetW() / 2;
	button->GetPos().y = y + MenuItems.size() * (text.GetSize() + buttongap);
	button->SetMenu(this);

	MenuItems.push_back(button);

	if(MenuItems.size() == 1) // If this is the first button, select it.
		button->Select();
}

//============================================================================================================================

void Menu::AddSelection(const string& default, vector<string> choices, Color& normal, Color& selected)
{
	Selection* selection = new Selection(default, choices, normal, selected);
	selection->GetPos().x = x + w/2 - text.GetStringWidth(default) / 2;
	selection->GetPos().y = y + MenuItems.size() * (text.GetSize() + buttongap);
	selection->SetMenu(this);

	MenuItems.push_back(selection);

	if(MenuItems.size() == 1) // If this is the first button, select it.
		selection->Select();
}

//============================================================================================================================

void Menu::Center()
{
	x = Screen::GetScreen().GetWidth()/2 - w/2;
	y = Screen::GetScreen().GetHeight()/2 - h/2;

	// Also center for menu's children
	for(int i = 0; i < MenuItems.size(); i++)
	{
		MenuItems[i]->GetPos().x = x + w/2 - MenuItems[i]->GetW()/2;
		MenuItems[i]->GetPos().y = y + i * (text.GetSize() + buttongap);
	}
}

//============================================================================================================================

// Sets the gap between buttons in pixels
void Menu::SetButtonGap(int buttongap)
{
	if(buttongap >= 0)
		this->buttongap = buttongap;
}

//============================================================================================================================

// Sets the transparency for buttons that are not selected in the menu
void Menu::SetAlphaUnSelected(float alpha)
{
	if(alpha >= 0.f && alpha <= 1.f)
		this->alpha = alpha;
}

//============================================================================================================================

// Sets the sound that is heard when buttons become selected
void Menu::SetSound(const string& soundname)
{
	this->soundname = soundname;
}

//============================================================================================================================

void Menu::Show()
{
	visible = true;

	// Reset all items
	if(!MenuItems.empty())
	{
		for(int i = 0; i < MenuItems.size(); i++)
		{
			MenuItems[i]->Deselect();
			MenuItems[i]->Clicked(false);
		}

		selected = 0;
		MenuItems[0]->Select();
	}
}

//============================================================================================================================

void Menu::Hide()
{
	visible = false;
}

//============================================================================================================================

bool Menu::IsVisible()
{
	return visible;
}

//============================================================================================================================

// Returns the item (1, 2, 3 etc.) that was clicked, if any
int Menu::IsClicked()
{
	if(MenuItems.empty() || !IsVisible()) {return 0;}

	for(int i = 0; i < MenuItems.size(); i++)
	{
		if(MenuItems[i]->IsClicked())
			return (i + 1);
	}

	return 0;
}

//============================================================================================================================

string Menu::GetItemTitle(int id)
{
	if(id < 1 || id > MenuItems.size()) {return "";}

	return MenuItems[id - 1]->GetTitle();
}

//============================================================================================================================

Font* Menu::GetFont()
{
	return &font;
}

//============================================================================================================================

int Menu::GetX() const
{
	return x;
}

//============================================================================================================================

int Menu::GetY() const
{
	return y;
}

//============================================================================================================================

int Menu::GetWidth() const
{
	return w;
}

//============================================================================================================================

int Menu::GetHeight() const
{
	return h;
}

//============================================================================================================================

float Menu::GetAlpha() const
{
	return alpha;
}

//============================================================================================================================

int Menu::GetButtonGap() const
{
	return buttongap;
}

//============================================================================================================================

int Menu::GetNoItems() const
{
	return MenuItems.size();
}

//===========================================================================================================================