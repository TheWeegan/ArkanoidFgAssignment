#pragma once
#include <vector>
#include <random>

#include "grid.h"
#include "brickFactory.h"

enum class Directions {
	Up,
	Down,
	Left,
	Right,
	Count
};

class LevelCreator {
public:
	LevelCreator();
	~LevelCreator();

	void DrunkardWalk(std::array<std::array<GridTile, gridSizeY>, gridSizeX>& grid, BrickType brickType,
		unsigned int randomMinIndexX, unsigned int randomMaxIndexX, unsigned int randomMinIndexY, unsigned int randomMaxIndexY);

private:
	bool IsValidTile(std::array<std::array<GridTile, gridSizeY>, gridSizeX> grid,
		unsigned int newIndexX, unsigned int newIndexY);
	bool TileInBounds(unsigned int currentIndexX, unsigned int currentIndexY);
	bool IsSurrounded(std::array<std::array<GridTile, gridSizeY>, gridSizeX> grid,
		unsigned int newIndexX, unsigned int newIndexY, unsigned int neighborLimit, TileType tileType);
	
	unsigned int RandomNumber(std::default_random_engine randomEngine, unsigned int min, unsigned int max);
	
	std::random_device randomSeed;
};

