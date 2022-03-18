#pragma once
#include <array>
#include <memory>

const unsigned int gridSizeX = 20;
const unsigned int gridSizeY = 15;

enum class TileType {
	Empty,
	NormalBlockPlaced,
	MetalBlockPlaced,
	EnemyPlaced,
	Count
};

struct GridTile {
	float positionX;
	float positionY;
	unsigned int tileIndexX;
	unsigned int tileIndexY;

	TileType tileType;
};

class GridHandler {
public:
	std::array<std::array<GridTile, gridSizeY>, gridSizeX> CreateGrid();	
	std::array<std::array<GridTile, gridSizeY>, gridSizeX> ResetGrid();

	void Draw();

private:
	std::array<std::array<GridTile, gridSizeY>, gridSizeX> grid;
	const float tileSizeX = 40.f;
	const float tileSizeY = 20.f;
};


