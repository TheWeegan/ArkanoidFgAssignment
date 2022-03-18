#include "levelCreator.h"
#include "game.h"

LevelCreator::LevelCreator() {}

LevelCreator::~LevelCreator() {}

void LevelCreator::DrunkardWalk(std::array<std::array<GridTile, gridSizeY>, gridSizeX>& grid, BrickType brickType,
	unsigned int randomMinIndexX, unsigned int randomMaxIndexX, unsigned int randomMinIndexY, unsigned int randomMaxIndexY) {

	std::default_random_engine randomEngine{ randomSeed() };

	unsigned int randomPositionX = RandomNumber(randomEngine, randomMinIndexX, randomMaxIndexX);
	unsigned int randomPositionY = RandomNumber(randomEngine, randomMinIndexY, randomMaxIndexY);

	while (grid[randomPositionX][randomPositionY].tileType != TileType::Empty) {
		std::default_random_engine randomEngine{ randomSeed() };
		randomPositionX = RandomNumber(randomEngine, randomMinIndexX, randomMaxIndexX);
		randomPositionY = RandomNumber(randomEngine, randomMinIndexY, randomMaxIndexY);
	}

	GridTile startTile = grid[randomPositionX][randomPositionY];
	unsigned int maxCount = (gridSizeX * gridSizeY) / (int)TileType::Count;
	unsigned int currentFloorCount = 1;

	unsigned int currentTileX = startTile.tileIndexX;
	unsigned int currentTileY = startTile.tileIndexY;
	grid[currentTileX][currentTileY].tileType = TileType::NormalBlockPlaced;

	float posX = grid[currentTileX][currentTileY].positionX;
	float posY = grid[currentTileX][currentTileY].positionY;
	allBricks.emplace_back(brickFactory.CreateBrick(posX, posY, 40.f, 20.f, brickType));


	std::uniform_int_distribution distribution(1, 4);

	while (currentFloorCount < maxCount) {
		int direction = distribution(randomEngine);

		unsigned int newTileX = currentTileX;
		unsigned int newTileY = currentTileY;

		switch (direction)
		{
		case 1: {
			newTileX = currentTileX;
			newTileY = currentTileY - 1;
			break;
		}
		case 2: {
			newTileX = currentTileX;
			newTileY = currentTileY + 1;
			break;
		}
		case 3: {
			newTileX = currentTileX - 1;
			newTileY = currentTileY;
			break;
		}
		case 4: {
			newTileX = currentTileX + 1;
			newTileY = currentTileY;
			break;
		}
		default:
			break;
		}

		if (TileInBounds(newTileX, newTileY)) {
			if (IsValidTile(grid, newTileX, newTileY)) {
				if (!IsSurrounded(grid, newTileX, newTileY, 4, TileType::NormalBlockPlaced)) {
					currentTileX = newTileX;
					currentTileY = newTileY;

					grid[currentTileX][currentTileY].tileType = TileType::NormalBlockPlaced;
					float posX = grid[currentTileX][currentTileY].positionX;
					float posY = grid[currentTileX][currentTileY].positionY;
					if (currentFloorCount % 5 == 0 && !IsSurrounded(grid, newTileX, newTileY, 3, TileType::MetalBlockPlaced)) {
						allBricks.emplace_back(brickFactory.CreateBrick(posX, posY, 40.f, 20.f, BrickType::MetalBrick));
					}
					else {
						allBricks.emplace_back(brickFactory.CreateBrick(posX, posY, 40.f, 20.f, brickType));
						brickAmount++;
					}

					currentFloorCount++;
				} else {
					break;
				}
			}
		}
	}
}

bool LevelCreator::IsValidTile(std::array<std::array<GridTile, gridSizeY>, gridSizeX> grid,
	unsigned int newIndexX, unsigned int newIndexY) {
	return (grid[newIndexX][newIndexY].tileType == TileType::Empty);
}

bool LevelCreator::TileInBounds(unsigned int newTileX, unsigned int newTileY) {
	return (newTileX < gridSizeX && newTileY < gridSizeY &&
		newTileX >= 0 && newTileY >= 0);
}

bool LevelCreator::IsSurrounded(std::array<std::array<GridTile, gridSizeY>, gridSizeX> grid, 
	unsigned int newIndexX, unsigned int newIndexY, unsigned int neighborLimit, TileType tileType) {
	int neighborsSurrounding = 0;

	if (TileInBounds(newIndexX + 1, newIndexY)) {
		if (grid[newIndexX + 1][newIndexY].tileType == tileType) {
			neighborsSurrounding++;
		}
	} else {
		neighborsSurrounding++;
	}
	if (TileInBounds(newIndexX, newIndexY + 1)) {
		if (grid[newIndexX][newIndexY + 1].tileType == tileType) {
			neighborsSurrounding++;
		}
	} else {
		neighborsSurrounding++;
	}
	if (TileInBounds(newIndexX - 1, newIndexY)) {
		if (grid[newIndexX - 1][newIndexY].tileType == tileType) {
			neighborsSurrounding++;
		}
	} else {
		neighborsSurrounding++;
	}
	if (TileInBounds(newIndexX, newIndexY - 1)) {
		if (grid[newIndexX][newIndexY - 1].tileType == tileType) {
			neighborsSurrounding++;
		}
	} else {
		neighborsSurrounding++;
	}
	return neighborsSurrounding >= neighborLimit;
}

unsigned int LevelCreator::RandomNumber(std::default_random_engine randomEngine, unsigned int min, unsigned int max) {
	std::uniform_int_distribution randomDist(min, max);
	unsigned int randomPosition = randomDist(randomEngine);

	return randomPosition;
}

