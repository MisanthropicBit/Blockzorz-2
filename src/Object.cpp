#include "Object.h"
#include "Graphics.h"
#include "Color.h"
#include <iostream>

//=========================================================================================================================

Object::Object()
{
	w = 0;
	h = 0;
	image = NULL;
	position.Zero();
	speed.Zero();
	acceleration.Zero();
	dead = false;
}

//=========================================================================================================================

Object::Object(const string& file, int w, int h)
{
	w = 0;
	h = 0;
	image = NULL;
	position.Zero();
	speed.Zero();
	acceleration.Zero();
	dead = false;

	Load(file, w, h);
}

//=========================================================================================================================

Object::Object(const string& file, Color& colorkey, int w, int h)
{
	w = 0;
	h = 0;
	image = NULL;
	position.Zero();
	speed.Zero();
	acceleration.Zero();
	dead = false;

	Load(file, colorkey, w, h);
}

//=========================================================================================================================

Object::~Object()
{
	if(image)
		SDL_FreeSurface(image);

	image = NULL;
}

//=========================================================================================================================

void Object::Load(const string& file, int w, int h)
{
	if((image = Graphics::LoadImage(file)) == NULL) {return;}

	this->w = w;
	this->h = h;
}

//=========================================================================================================================

void Object::Load(const string& file, Color& colorkey, int w, int h)
{
	if((image = Graphics::LoadImage(file)) == NULL) {return;}

	Graphics::SetTransparencyColor(image, colorkey);

	this->w = w;
	this->h = h;
}

//=========================================================================================================================

void Object::Draw()
{
	if(!image)
	{
		cerr << "Error (Object): Unable to draw Object. No image data available" << endl;
		return;
	}

	Graphics::DrawImage(image, position.x, position.y);
}

//=========================================================================================================================

void Object::Update(int dt)
{
	speed += acceleration;
	position += speed * dt;
}

//=========================================================================================================================

void Object::SetImage(SDL_Surface* newimage)
{
	if(image)
		SDL_FreeSurface(image);

	image = NULL;
	image = newimage;
}

//=========================================================================================================================

SDL_Surface* Object::GetImage() const
{
	return image;
}

//========================================================================================================================

bool Object::IsDead() const
{
	return dead;
}

//=========================================================================================================================