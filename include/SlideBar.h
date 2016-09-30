#ifndef SLIDE_BAR_H
#define SLIDE_BAR_H

#include "Event.h"
#include "Vector.h"

#include <string>
using namespace std;

class SlideBar : public Event
{
	public:
		SlideBar();
		SlideBar(const string& imagefile, int x, int y, int min, int max);
		~SlideBar();

		bool Load(const string& imagefile, int x, int y, int min, int max);
		void OnEvent(SDL_Event& event);
		void Draw();

		void SetValue(int value);
		void SetMin(int min);
		void SetMax(int max);
		int GetValue() const;

		bool HasMouseHover(int mx, int my);
		void OnMouseMove(int mx, int my, int relx, int rely, Uint8 state);
		void OnLeftButtonDown(int mx, int my);
		void OnLeftButtonUp(int mx, int my);

	private:
		Vector position;
		int ix; // Image x-coordinate
		int relx;
		int value;
		int min;
		int max;
		bool pressed;
		SDL_Surface* image;
};

#endif