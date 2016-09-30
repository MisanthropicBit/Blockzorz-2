#ifndef BUTTON_H
#define BUTTON_H

#include "Font.h"
#include "Color.h"

#include <string>
using namespace std;

class Button
{
	public:
		Button();
		~Button();

		virtual bool Load(const string& caption, const string& fontfile, Color& color, int size, int x, int y);
		virtual void Draw();

		void SetAlpha(float alpha);
		void Select();
		void Deselect();
		bool IsSelected() const;

		bool HasMouseHover(int mx, int my);
		virtual void OnMouseMove(int mx, int my);

	protected:
		bool hover;
		bool selected;
		SDL_Rect rect;
		string caption;
		SDL_Surface* image;
		float alpha;
};

//=========================================================================================================================

class AnimatedButton : public Button
{
	public:
		AnimatedButton();
		~AnimatedButton();

		bool Load(const string& imagefile, int x, int y);
		void Draw();

		void SetFrame(int frame);
		int GetFrame() const;

	private:
		int frame;
};

#endif