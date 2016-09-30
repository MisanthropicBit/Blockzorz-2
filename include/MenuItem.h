#ifndef MENUITEM_H
#define MENUITEM_H

//=========================================================================================================================

#include "Object.h"
#include "Color.h"
#include "SDL.h"
#include <vector>
using namespace std;

//=========================================================================================================================

class Font;
class Menu;

//=========================================================================================================================

// Abstract base class
class MenuItem : public Object
{
	public:
		MenuItem(Color& normal, Color& selected);

		virtual bool OnMouseMotion(int x, int y);
		virtual bool OnMouseButtonDown(int x, int y);
		virtual void OnMouseButtonUp();
		virtual void OnEnter() = 0;
		virtual bool OnRightKey() = 0;
		virtual bool OnLeftKey() = 0;

		virtual void Draw() = 0;

		void Clicked(bool flag);
		void Select();
		void Deselect();
		//void Cursor(bool flag);

		bool IsClicked() const;
		bool HasHover() const;
		bool HasCursor() const;
		virtual string GetTitle() const;

		void SetMenu(Menu* menu);


	protected:
		Color normal;
		Color selected;
		bool clicked;
		bool hover;
		bool cursor;

		Menu* menu; // pointer to parent
};

//=========================================================================================================================

class Button : public MenuItem
{
	public:
		Button(const string& title, Color& normal, Color& selected, int w, int h);
		~Button();

		bool OnMouseMotion(int x, int y);
		bool OnMouseButtonDown(int x, int y);
		void OnMouseButtonUp();
		void OnEnter();
		bool OnRightKey();
		bool OnLeftKey();

		void RenderItem();

		string GetTitle() const;

	protected:
		string title;
};

//=========================================================================================================================

//class AnimatedButton : public MenuItem
//{
//	public:
//		Animation anim;
//
//	private:
//};

//=========================================================================================================================

class Selection : public MenuItem
{
	public:
		Selection(const string& default, vector<string> choices, Color& normal, Color& selected);

		void AddChoice(const string& choice);

		bool OnMouseMotion(int x, int y);
		void OnEnter();
		bool OnRightKey();
		bool OnLeftKey();

		void Draw();

		string GetTitle() const;

	private:
		int chosen;
		vector<string> Choices;
};

//=========================================================================================================================

#endif