#ifndef OPTION_BUTTON_H
#define OPTION_BUTTON_H

#include "Button.h"
#include "Event.h"
#include "Font.h"
#include "Vector.h"

#include <vector>
#include <string>
using namespace std;

class OptionButton : public Event
{
	public:
		OptionButton();
		~OptionButton();

		bool Load(const string& fontfile, Color& color, int size, int x, int y);
		void Draw();

		void AddSelection(const string& selection);
		bool SetSelection(const string& selection);
		void SetAlpha(float alpha);
		string GetSelection();

		void Select();
		void Deselect();
		bool IsSelected() const;

		bool HasMouseHover(int mx, int my);

		void OnLeftButtonDown(int mx, int my);
		void OnMouseMove(int mx, int my);

	private:
		bool selected;
		int current;
		float alpha;
		SDL_Rect rect;
		Color color;
		Font font;
		vector<string> selections;
};

#endif