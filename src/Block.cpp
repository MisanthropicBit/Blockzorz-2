#include "Block.h"
#include "Graphics.h"
#include "Grid.h"
#include "Screen.h"
#include <math.h>

//=========================================================================================================================

Block::Block()
{
	row = 0;
	col = 0;
	swapx = 0;
	swapy = 0;
	dropy = 0;
	type = BLOCK_TYPE_NOGOOD;
	isfalling  = false;
	isswapping = false;
	check      = false;
	animation.SetCurrentFrame(0);
	animation.SetMaxFrames(2);
	animation.Stop();
}

//=========================================================================================================================

Block::Block(BlockType type, int row, int col) : AnimatedObject()
{
	swapx = 0;
	swapy = 0;
	dropy = 0;
	isfalling  = false;
	isswapping = false;
	check      = false;
	animation.SetCurrentFrame(0);
	animation.SetMaxFrames(2);
	animation.Stop();

	if(type < BLOCK_TYPE_RED || type > BLOCK_TYPE_NOGOOD)
		this->type = BLOCK_TYPE_NOGOOD;
	else
	{
		this->type = type;

		switch(type)
		{
			case BLOCK_TYPE_RED:
				Load("./Graphics/Animations/RedBlock.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_BLUE:
				Load("./Graphics/Animations/BlueBlock.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_GREEN:
				Load("./Graphics/Animations/GreenBlock.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_YELLOW:
				Load("./Graphics/Animations/YellowBlock.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			case BLOCK_TYPE_PURPLE:
				Load("./Graphics/Animations/PurpleBlock.png", BLOCK_WIDTH, BLOCK_HEIGHT);
				break;

			default:
				break;
		}
	}

	if(row >= 0 && row < GRID_MAX_ROWS && col >= 0 && col < GRID_MAX_COLUMNS)
	{
		this->row = row;
		this->col = col;
		position.x = 220 + col * w;
		position.y = row * h + 50;
	}
}

//=========================================================================================================================

Block::~Block()
{
}

//=========================================================================================================================

void Block::Update(int dt)
{
	Object::Update(dt);

	if(!Grid::GameGrid().IsSpawning())
	{
		if(isswapping)
		{
			if(speed.x < 0 && position.x <= swapx || speed.x > 0 && position.x >= swapx)
			{
				speed.Zero();
				position.x = swapx;
				isswapping = false;

				if(!Grid::GameGrid().GetBlock(row + 1, col))
					Fall();
				else if(Grid::GameGrid().GetBlock(row + 1, col))
				{
					if(Grid::GameGrid().GetBlock(row + 1, col)->IsFalling())
						Fall();
					else
						check = true;
				}
			}
		}
		else if(isfalling)
		{
			if(position.y + h >= Grid::GameGrid().GetRowYCoord(GRID_MAX_ROWS)) // The block reached the bottom
			{
				position.y = Grid::GameGrid().GetRowYCoord(GRID_MAX_ROWS - 1);
				speed.Zero();
				isfalling = false;
				check = true;
			}
			else if(Grid::GameGrid().GetBlock(row + 1, col)) // There is a block below it
			{
				Block* nextblock = Grid::GameGrid().GetBlock(row + 1, col);

				if(!nextblock->IsFalling() && !nextblock->IsDead())
				{
					if(position.y + h >= nextblock->position.y)
					{
						position.y = nextblock->position.y - h;
						speed.Zero();
						isfalling = false;
						check = true;
					}
				}
			}
			else if(!Grid::GameGrid().GetBlock(row + 1, col)) // There is not a block below it
			{
				if(position.y + h > Grid::GameGrid().GetRowYCoord(row + 1))
				{
					Grid::GameGrid().SetBlock(this, row + 1, col);
					Grid::GameGrid().SetBlockEmpty(row, col);
					++row;
				}
			}
		}
	}
	else
	{
		if(position.y >= dropy)
		{
			position.y = dropy;
			speed.Zero();
		}
	}
}

//=========================================================================================================================

void Block::Draw()
{
	AnimatedObject::Draw();
}

//=========================================================================================================================

void Block::Fall()
{
	if(!dead)
	{
		speed = Vector(0, FALL_SPEED);
		isfalling = true;
	}
}

//=========================================================================================================================

void Block::Kill()
{
	dead = true;
}

//=========================================================================================================================

void Block::SwapLeft()
{
	speed.x = -SWAP_SPEED;
	swapx = position.x - w;
	--col;
	isswapping = true;
}

//=========================================================================================================================

void Block::SwapRight()
{
	speed.x = SWAP_SPEED;
	swapx = position.x + w;
	++col;
	isswapping = true;
}

//=========================================================================================================================

void Block::Check()
{
	check = true;
}

//=========================================================================================================================

bool Block::NeedsChecking() const
{
	return check;
}

//=========================================================================================================================

void Block::DontCheck()
{
	check = false;
}

//=========================================================================================================================

bool Block::IsDead() const
{
	return dead;
}

//=========================================================================================================================

bool Block::IsFalling() const
{
	return isfalling;
}

//=========================================================================================================================

bool Block::IsSwapping() const
{
	return isswapping;
}

//=========================================================================================================================

BlockType Block::GetBlockType() const
{
	return type;
}

//=========================================================================================================================

int Block::GetDropY() const
{
	return dropy;
}

//=========================================================================================================================

void Block::SetDropY(int dropy)
{
	this->dropy = dropy;
}

//=========================================================================================================================

int Block::GetRow() const
{
	return row;
}

//=========================================================================================================================

int Block::GetCol() const
{
	return col;
}

//=========================================================================================================================