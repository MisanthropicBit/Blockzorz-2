#ifndef OBJECT_H
#define OBJECT_H

#include "SDL.h"
#include "Vector.h"
#include "Color.h"

#include <string>
using namespace std;

class Object
{
	public:
		Object();
		Object(const string& file, int w, int h);
		Object(const string& file, Color& colorkey, int w, int h);
		~Object();

		void Load(const string& file, int w, int h);
		void Load(const string& file, Color& colorkey, int w, int h);
		virtual void Draw();
		virtual void Update(int dt);

		void SetImage(SDL_Surface* newimage);
		SDL_Surface* GetImage() const;
		bool IsDead() const;

	public:
		int w, h;
		Vector position;
		Vector speed;
		Vector acceleration;

	protected:
		SDL_Surface* image;
		bool dead;
};

#endif