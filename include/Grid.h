#ifndef GRID_H
#define GRID_H

#include "Block.h"
#include "ParticleEffectManager.h"
#include "Font.h"

#include <vector>
using namespace std;

// Constants
const int GRID_MAX_ROWS    = 14;
const int GRID_MAX_COLUMNS = 8;
const int SPAWN_RATE       = 3000;
const int SPAWN_INTERVAL   = 30000;
const int START_SPAWN_INTERVAL = 60;
const int MAX_INCREASES = 10;
const int SPAWN_DECAY = 250;
const float SPAWN_DROP_SPEED = 0.8f;
const int POINTS_PER_BLOCK   = 5;
const int COMBO_POINTS       = 20; // Old value = 7
//const int COMBO_EXTRA_POINTS = 20;

class Grid
{
	public:
		~Grid();

		static Grid& GameGrid();

		void Update(int dt);
		void Draw();
		void Spawn();
		void DeSpawn();
		void SpawnBlockAtTop();
		bool IsGameOver();
		bool IsSpawning() const;
		
		void SwapBlocks(int row, int col);
		void CheckBlock(int row, int col);
		BlockType ValidateBlock(int row, int col);
		
		void SetWidth(int width);
		void SetHeight(int height);
		void SetBlock(Block* block, int row, int col);
		void SetBlockEmpty(int row, int col);
		Block* GetBlock(int row, int col);
		int GetWidth() const;
		int GetHeight() const;
		int GetNoCombos() const;
		int GetScore() const;
		int GetRowYCoord(int row);
		int GetColXCoord(int col);
		int GetFinalScore();
		int GetHighestBlock();

		void PrintGrid(); // For debug purposes
		
	private:
		Grid(); // hidden constructor
		static Grid gamegrid;

		int width;
		int height;
		int combos;
		int score;
		bool gameover;

		// In-game spawn variables
		int spawntime;
		int spawninterval;
		int increased;

		// Initial spawning variables
		bool spawning;
		int spawntimeleft;
		int startspawninterval;
		int spawnrow;
		int spawncol;

		Block* grid[GRID_MAX_ROWS][GRID_MAX_COLUMNS];
		vector<Block*> SpawnList;
		void SpawnBlocks(int dt);
		ParticleEffectManager peManager;
		Font debugtext;
};

#endif