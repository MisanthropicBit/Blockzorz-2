#ifndef BLOCKZORZ2_OBJECT_HPP
#define BLOCKZORZ2_OBJECT_HPP

#include <SDL.h>
#include <string>
#include "vector2.hpp"
#include "color.hpp"

class object {
	public:
		object();
		object(const std::string& file, int w, int h);
		object(const std::string& file, const color& colorkey, int w, int h);
		~object();

		void load(const std::string& file, int w, int h);
		void load(const std::string& file, const color& colorkey, int w, int h);
		virtual void draw();
		virtual void update(int dt);

		void set_image(SDL_Surface* image);
		SDL_Surface* image() const;
		bool dead() const;

	public:
		int w, h;
		vector2 position;
		vector2 speed;
		vector2 acceleration;

	protected:
		SDL_Surface* image;
		bool dead;
};

#endif
