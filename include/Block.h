#ifndef BLOCK_H
#define BLOCK_H

#include "AnimatedObject.h"

#include <string>
using namespace std;

const int BLOCK_WIDTH  = 25;
const int BLOCK_HEIGHT = 25;
const float SWAP_SPEED = 0.5f; // Speed at which the blocks swap
const float FALL_SPEED = 0.1f; // The speed blocks fall with when the game is in progress

enum BlockType
{
	BLOCK_TYPE_RED = 0,
	BLOCK_TYPE_BLUE,
	BLOCK_TYPE_GREEN,
	BLOCK_TYPE_YELLOW,
	BLOCK_TYPE_PURPLE,
	BLOCK_TYPE_NOGOOD
};

//===========================================================================================================================================================

class Block : public AnimatedObject
{
	public:
		Block();
		Block(BlockType type, int row, int col);
		~Block();

		virtual void Update(int dt);
		virtual void Draw();

		void Fall();
		void Kill();
		void SwapLeft();
		void SwapRight();
		void Check();
		void DontCheck();
		void SetDropY(int dropy);

		bool NeedsChecking() const;
		bool IsDead() const;
		bool IsFalling() const;
		bool IsSwapping() const;
		BlockType GetBlockType() const;
		int GetDropY() const;
		int GetRow() const;
		int GetCol() const;

	protected:
		int row;
		int col;
		int swapx;
		int swapy;
		int dropy;
		BlockType type;
		bool isfalling;
		bool isswapping;
		bool check;
};

#endif