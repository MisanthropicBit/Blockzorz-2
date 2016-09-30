#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

#include <string>
using namespace std;

class Player
{
	public:
		Player();
		Player(const string& file, int row, int col);
		~Player();

		void Load(const string& file, int row, int col);
		void Update(int dt);
		void Draw();

		void SetTransparency(float alpha);
		int& GetRow();
		int& GetColumn();

		void StartMovingUp();
		void StartMovingDown();
		void StartMovingLeft();
		void StartMovingRight();

		void StopMoving();

	private:
		SDL_Surface* image;
		int row;
		int col;
		int movex;
		int movey;
		int keydelay;
};

#endif