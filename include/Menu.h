#ifndef MENU_H
#define MENU_H

/*
This class, along with the MenuItem class, constitutes a simple gui to deal with menus for a game.
*/

#include "Font.h"
#include <vector>
using namespace std;

class MenuItem;

class Menu
{
	public:
		Menu(const string& title = "", const string& fontfile = "", int fontsize = 0, const string& imagefile = "", int x = 0, int y = 0); // uses the image's width and height
		~Menu();

		void Load(const string& title = "", const string& fontfile = "", int fontsize = 0, const string& imagefile = "", int x = 0, int y = 0);

		void HandleEvent(SDL_Event& event);
		void Draw();

		void AddMenuItem(MenuItem* item);
		void AddButton(const string& title, Color& normal, Color& select);
		void AddSelection(const string& default, vector<string> choices, Color& normal, Color& select);
		void Center();
		void SetButtonGap(int buttongap);
		void SetAlphaUnSelected(float alpha);
		void SetSound(const string& soundname);

		void Show();
		void Hide();
		bool IsVisible();
		int IsClicked();
		string GetItemTitle(int id);

		Font* GetFont();
		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;
		float GetAlpha() const;
		int GetButtonGap() const;
		int GetNoItems() const;

		int selected; // Button that is currently selected
	private:
		int x;
		int y;
		int w;
		int h;
		bool visible;
		int buttongap;
		float alpha;
		string soundname;
		SDL_Surface* image;
		Font font;

		vector<MenuItem*> MenuItems;
};

#endif