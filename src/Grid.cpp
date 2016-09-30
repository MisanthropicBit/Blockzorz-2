#include "Grid.h"
#include "Block.h"
#include "AudioManager.h"
#include "ParticleEffect.h"
#include "Game.h"
#include <stdio.h>
#include <iostream>
using namespace std;

//=========================================================================================================================

Grid Grid::gamegrid;

//=========================================================================================================================

Grid::Grid()
{
	for(int r = 0; r < GRID_MAX_ROWS; r++)
	{
		for(int c = 0; c < GRID_MAX_COLUMNS; c++)
		{
			grid[r][c] = NULL;
		}
	}
	
	combos = 0;
	score  = 0;
	spawntime = SPAWN_RATE;
	spawninterval = SPAWN_INTERVAL;
	startspawninterval = START_SPAWN_INTERVAL;
	increased = 0;
	gameover = false;
	spawning = false;
	spawntimeleft = 0;
	spawnrow = 13;
	spawncol = 0;
	SpawnList.clear();
}

//=========================================================================================================================

Grid::~Grid()
{
	for(int r = 0; r < GRID_MAX_ROWS; r++)
	{
		for(int c = 0; c < GRID_MAX_COLUMNS; c++)
		{
			if(grid[r][c])
			{
				delete grid[r][c];
				grid[r][c] = NULL;
			}
		}
	}

	for(int i = 0; i < SpawnList.size(); i++)
	{
		if(SpawnList[i])
			delete SpawnList[i];
	}

	SpawnList.clear();
}

//=========================================================================================================================

Grid& Grid::GameGrid()
{
	return Grid::gamegrid;
}

//=========================================================================================================================

void Grid::Update(int dt)
{
	if(!spawning)
	{
		peManager.Update(dt);
		spawntime -= dt;
		if(increased < MAX_INCREASES)
		{
			spawninterval -= dt;

			if(spawninterval <= 0)
			{
				increased++;
				spawninterval = SPAWN_INTERVAL;
			}
		}

		if(spawntime <= 0)
		{
			SpawnBlockAtTop();
			spawntime = SPAWN_RATE - increased * SPAWN_DECAY;
		}

		if(!SpawnList.empty())
		{
			for(int i = 0; i < SpawnList.size(); i++)
			{
				SpawnList[i]->Object::Update(dt);

				if(SpawnList[i]->position.y + SpawnList[i]->h >= GetRowYCoord(0))
				{
					if(grid[0][SpawnList[i]->GetCol()])
						gameover = true;
					else
					{
						SpawnList[i]->Fall();
						grid[0][SpawnList[i]->GetCol()] = SpawnList[i];
						SpawnList.erase(SpawnList.begin() + i);
					}
				}
			}
		}
	}
	else
		SpawnBlocks(dt);

	for(int r = 0; r < GRID_MAX_ROWS; ++r)
	{
		for(int c = 0; c < GRID_MAX_COLUMNS; ++c)
		{
			if(grid[r][c])
			{
				if(grid[r][c]->IsDead())
				{
					ParticleExplosionEffect* pex = new ParticleExplosionEffect("./Graphics/Images/Cursor.png", 6, 0.1f, 0.1f, GetColXCoord(c) + grid[r][c]->w/2, GetRowYCoord(r) + grid[r][c]->h/2);
					pex->SetUpdateInterval(40, 80);
					pex->Show();
					peManager.AddEffect(pex);
					
					delete grid[r][c];
					grid[r][c] = NULL;
				}
				else
				{
					if(grid[r][c]->NeedsChecking())
						CheckBlock(r, c);

					grid[r][c]->Update(dt);
				}
			}
		}
	}
}

//=========================================================================================================================

void Grid::Draw()
{
	for(int r = 0; r < GRID_MAX_ROWS; r++)
	{
		for(int c = 0; c < GRID_MAX_COLUMNS; c++)
		{
			if(grid[r][c])
				grid[r][c]->Draw();
		}
	}

	if(!SpawnList.empty())
	{
		for(int i = 0; i < SpawnList.size(); i++)
		{
			SpawnList[i]->Draw();
		}
	}

	peManager.Draw();
}

//=========================================================================================================================

void Grid::Spawn()
{
	combos = 0;
	score  = 0;
	gameover = false;
	spawning = true;
	increased = 0;
	spawnrow = 13;
	spawncol = 0;

	debugtext.SetFontFile("./Fonts/biocomv2.ttf", 30);
}

//=========================================================================================================================

void Grid::DeSpawn()
{
	for(int r = 0; r < GRID_MAX_ROWS; r++)
	{
		for(int c = 0; c < GRID_MAX_COLUMNS; c++)
		{
			if(grid[r][c])
			{
				delete grid[r][c];
				grid[r][c] = NULL;
			}
		}
	}

	for(int i = 0; i < SpawnList.size(); i++)
	{
		if(SpawnList[i])
			delete SpawnList[i];
	}

	SpawnList.clear();
	debugtext.Close();
	peManager.Clear();
}

//=========================================================================================================================

void Grid::SpawnBlockAtTop()
{
	int randcol = rand() % 8;

	if(grid[0][randcol])
	{
		gameover = true;
	}
	else
	{
		Block* block = new Block(static_cast<BlockType>(rand() % 5), 0, randcol);
		block->position = Vector(GetColXCoord(randcol), -BLOCK_HEIGHT);
		block->speed = Vector(0, FALL_SPEED);
		SpawnList.push_back(block);
		block = NULL;
	}
}

//=========================================================================================================================

void Grid::SwapBlocks(int row, int col)
{
	// If there is nothing to swap, don't bother
	if(!grid[row][col] && !grid[row][col + 1])
		return;

	PrintGrid();

	Block* block1 = grid[row][col];
	Block* block2 = grid[row][col + 1];
	int col2 = col + 1;

	if(block1) // If there is a block at the 1st position
	{
		if(!block1->IsFalling() && !block1->IsDead()) // This block is neither falling or dead
		{
			if(block2) // There is a block besides this block
			{
				if(!block2->IsFalling() && !block2->IsDead()) // This block is not falling or dead
					block1->SwapRight(); // Swap
			}
			else if(!block2) // If there is not a block besides it
			{
				if(row != GRID_MAX_ROWS - 1) // If we are not at the bottom row
				{
					if(grid[row + 1][col2]) // If there is a block below and to the right of block1
					{
						if(grid[row + 1][col2]->IsFalling() && !grid[row + 1][col2]->IsDead()) // If this block is falling and not dead
						{
							if(grid[row + 1][col2]->position.y >= GetRowYCoord(row + 1)) // The block has passed by
								block1->SwapRight(); // Swap
						}
						else
							block1->SwapRight(); // No block besides it, not at bottom row, block below and to the right
												 // and that block is not falling and dead
					}
					else
						block1->SwapRight(); // No block besides it, there is not a block below and to the right
				}
				else
					block1->SwapRight(); // No block beside it, we are at the bottom row
			}
		}
	}

	PrintGrid();

	if(block2)
	{
		if(!block2->IsFalling() && !block2->IsDead())
		{
			if(block1)
			{
				if(!block1->IsFalling() && !block1->IsDead())
					block2->SwapLeft();
			}
			else if(!block1)
			{
				if(row != GRID_MAX_ROWS - 1)
				{
					if(grid[row + 1][col])
					{
						if(grid[row + 1][col]->IsFalling() && !grid[row + 1][col]->IsDead())
						{
							if(grid[row + 1][col]->position.y >= GetRowYCoord(row + 1)) // Block has passed
								block2->SwapLeft(); // If there is no block besides it, swap
						}
						else
							block2->SwapLeft();
					}
					else
						block2->SwapLeft();
				}
				else
					block2->SwapLeft();
			}
		}
	}

	PrintGrid();

	//if(block1)
	//{
	//	if(block1->IsSwapping())
	//	{
	//		grid[row][col2] = block1;
	//		grid[row][col]  = block2;
	//	}
	//}
	//else if(block2)
	//{
	//	if(block2->IsSwapping())
	//	{
	//		grid[row][col2] = block1;
	//		grid[row][col]  = block2;
	//	}
	//}

	// The following code we check to see whether or not we need to change
	// the pointers stored in the 'grid' object if the blocks are swapping.
	if(block1 && block2)
	{
		if(block1->IsSwapping() && block2->IsSwapping())
		{
			grid[row][col2] = block1;
			grid[row][col] = block2;
		}
	}
	else if(block1 && !block2)
	{
		if(block1->IsSwapping())
		{
			grid[row][col2] = block1;
			grid[row][col] = NULL;
		}
	}
	else if(!block1 && block2)
	{
		if(block2->IsSwapping())
		{
			grid[row][col] = block2;
			grid[row][col2] = NULL;
		}
	}

	// Move blocks above empty space if necessary
	if(!block1 && row != 1)
	{
		for(int i = row - 1; i >= 1; --i)
		{
			if(grid[i][col2])
				grid[i][col2]->Fall();
			else
				break;
		}
	}
	if(!block2 && row != 1)
	{
		for(int i = row - 1; i >= 1; --i)
		{
			if(grid[i][col])
				grid[i][col]->Fall();
			else
				break;
		}
	}

	PrintGrid();
}

//=========================================================================================================================

void Grid::CheckBlock(int row, int col)
{
	int score = 0;

	// Is the block even valid?
	if(ValidateBlock(row, col) == BLOCK_TYPE_NOGOOD)
		return;

	BlockType blocktype = grid[row][col]->GetBlockType(); // Get the block's type

	int connectedabove = 0;
	int connectedbelow = 0;
	//bool pointsAboveOrBelow = false;

	// Check above block
	for(int i = row - 1; i >= 0; --i)
	{
		if(ValidateBlock(i, col) == blocktype)
			++connectedabove;
		else
			break;
	}

	// Check below block
	for(int i = row + 1; i < GRID_MAX_ROWS; ++i)
	{
		if(ValidateBlock(i, col) == blocktype)
			++connectedbelow;
		else
			break;
	}

	if(connectedabove + connectedbelow >= 2)
	{
		//pointsAboveOrBelow = true;
		score += connectedabove + connectedbelow;

		for(int i = row + connectedbelow; i >= row - connectedabove; --i)
			grid[i][col]->Kill();

		for(int i = row - connectedabove - 1; i >= 0; --i)
		{
			if(ValidateBlock(i, col) != BLOCK_TYPE_NOGOOD)
				grid[i][col]->Fall();
			else
				break;
		}
	}

	int connectedleft  = 0;
	int connectedright = 0;

	// Check left of block
	for(int i = col - 1; i >= 0; --i)
	{
		if(ValidateBlock(row, i) == blocktype)
			++connectedleft;
		else
			break;
	}
	// Check right of block
	for(int i = col + 1; i < GRID_MAX_COLUMNS; ++i)
	{
		if(ValidateBlock(row, i) == blocktype)
			++connectedright;
		else
			break;
	}

	if(connectedleft + connectedright >= 2) // We need at least three connected blocks
	{
		score += connectedleft + connectedright; // Add to score

		for(int i = col - connectedleft; i <= col + connectedright; ++i) // Run through blocks again and kill them
			grid[row][i]->Kill();

		for(int i = col - connectedleft; i <= col + connectedright; ++i) // Run through blocks than now need to fall
		{
			//if(pointsAboveOrBelow && i == col) // Points scored in vertical direction, don't make 
			//	continue;

			for(int j = row - 1; j >= 1; --j)
			{
				if(ValidateBlock(j, i) != BLOCK_TYPE_NOGOOD)
					grid[j][i]->Fall();
				else
					break;
			}
		}
	}

	if(score > 0) // If the player scored any points
	{
		score += 1; // For the block we're checking
		grid[row][col]->Kill();

		if(Game::gamesettings.CFmodeunlocked)
			AudioManager::GetManager()->PlaySound("Yes!", 0);

		if(score > 3) // More than three blocks connected counts as a combo
		{
			++combos;
			score *= POINTS_PER_BLOCK;
			score += COMBO_POINTS * (score - 3);
		}
		else
			score *= POINTS_PER_BLOCK;

		this->score += score;

		//AudioManager::GetManager()->PlaySound("Explosion", 0);
	}
	else
		grid[row][col]->DontCheck(); // If no points were scored, don't check this block anymore
}

//=========================================================================================================================

BlockType Grid::ValidateBlock(int row, int col)
{
	if(row < 0 || row >= GRID_MAX_ROWS || col < 0 || col >= GRID_MAX_COLUMNS || !grid[row][col])
		return BLOCK_TYPE_NOGOOD; // If we are out of bounds or there is nothing in this position, return "false"

	if(grid[row][col])
	{
		if(grid[row][col]->IsFalling() || grid[row][col]->IsDead()) // If there is a block but it is falling or dead, return "false"
			return BLOCK_TYPE_NOGOOD;
	}

	return grid[row][col]->GetBlockType();
}

//=========================================================================================================================

void Grid::SetWidth(int width)
{
	this->width = width;
}

//=========================================================================================================================

void Grid::SetHeight(int height)
{
	this->height = height;
}

//=========================================================================================================================

bool Grid::IsGameOver()
{
	for(int i = 0; i < GRID_MAX_COLUMNS; i++)
	{
		if(grid[0][i])
		{
			if(!grid[0][i]->IsFalling())
				return true;
		}
	}

	return false;
}

//=========================================================================================================================

bool Grid::IsSpawning() const
{
	return spawning;
}

//=========================================================================================================================

void Grid::SetBlockEmpty(int row, int col)
{
	grid[row][col] = NULL;
}

//=========================================================================================================================

void Grid::SetBlock(Block* block, int row, int col)
{
	if(row >= GRID_MAX_ROWS || col >= GRID_MAX_COLUMNS || !block) {return;}

	grid[row][col] = block;
}

//=========================================================================================================================

Block* Grid::GetBlock(int row, int col)
{
	if(row < 0 || row >= GRID_MAX_ROWS || col < 0 || col >= GRID_MAX_COLUMNS) {return NULL;}

	return grid[row][col];
}

//=========================================================================================================================

int Grid::GetRowYCoord(int row)
{
	return (50 + (row * BLOCK_HEIGHT));
}

//=========================================================================================================================

int Grid::GetColXCoord(int col)
{
	return (220 + (col * BLOCK_WIDTH));
}

//=========================================================================================================================

int Grid::GetWidth() const
{
	return width;
}

//=========================================================================================================================

int Grid::GetHeight() const
{
	return height;
}

//=========================================================================================================================

int Grid::GetNoCombos() const
{
	return combos;
}

//=========================================================================================================================

int Grid::GetScore() const
{
	return score;
}

//=========================================================================================================================

void Grid::SpawnBlocks(int dt)
{
	spawntimeleft -= dt;

	if(spawntimeleft <= 0)
	{
		spawntimeleft = startspawninterval;

		// Spawn a new block...
		if(spawnrow > 6) // ...If we are still in a row below 6
		{
			int random = rand() % 5;
			int leftspawncol  = (spawncol - 1 < 0 ? spawncol : spawncol - 1);
			int belowspawnrow = (spawnrow == GRID_MAX_ROWS - 1 ? spawnrow : spawnrow + 1);

			if(leftspawncol != spawncol)
			{
				if(grid[spawnrow][leftspawncol])
				{
					if(grid[spawnrow][leftspawncol]->GetBlockType() == static_cast<BlockType>(random))
						random = (random - 1 < 0 ? 4 : random - 1);
				}
			}

			if(belowspawnrow != spawnrow)
			{
				if(grid[belowspawnrow][spawncol])
				{
					if(grid[belowspawnrow][spawncol]->GetBlockType() == static_cast<BlockType>(random))
						random = (random - 1 < 0 ? 4 : random - 1);
				}
			}

			Block* block = new Block(static_cast<BlockType>(random), spawnrow, spawncol);
			block->position = Vector(GetColXCoord(spawncol), -BLOCK_HEIGHT);
			block->speed = Vector(0, SPAWN_DROP_SPEED);
			block->SetDropY(GetRowYCoord(spawnrow));
			grid[spawnrow][spawncol] = block;
			block = NULL;

			// Decrease row count if entire row has been spawned...
			if(spawncol >= GRID_MAX_COLUMNS - 1)
			{
				spawncol = 0;
				spawnrow--;
			}
			else // ...or move along
				spawncol++;
		}

		// If the last spawned block has reached its destination, stop spawning
		if(grid[GRID_MAX_ROWS/2][GRID_MAX_COLUMNS - 1])
		{
			if(grid[GRID_MAX_ROWS/2][GRID_MAX_COLUMNS - 1]->position.y == GetRowYCoord(GRID_MAX_ROWS/2))
			{
				spawning = false;
				if(Game::gamesettings.CFmodeunlocked)
					AudioManager::GetManager()->PlaySound("Moves", 0);
			}
		}
	}
}

//=========================================================================================================================

int Grid::GetFinalScore()
{
	return score;// + COMBO_POINTS * combos;
}

//=========================================================================================================================

int Grid::GetHighestBlock()
{
	for(int row = 0; row < GRID_MAX_ROWS; row++)
	{
		for(int col = 0; col < GRID_MAX_COLUMNS; col++)
		{
			if(grid[row][col])
			{
				if(! grid[row][col]->IsFalling() && !grid[row][col]->IsDead())
					return row;
			}
		}
	}
}

//=========================================================================================================================

void Grid::PrintGrid()
{
	for(int row = 0; row < GRID_MAX_ROWS; row++)
	{
		for(int col = 0; col < GRID_MAX_COLUMNS; col++)
		{
			if(grid[row][col])
			{
				if(grid[row][col]->IsFalling())
					cout << "F";
				else if(grid[row][col]->IsDead())
					cout << "D";
				else if(grid[row][col]->IsSwapping())
					cout << "S";
				else
					cout << "N";
			}
			else
				cout << "0";

			if(col == 7)
				cout << endl;
		}
	}

	cout << endl;
}

//=========================================================================================================================