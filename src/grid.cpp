#include "grid.h"
#include "bizarreEngine.h"
#include "collision.h"


std::array<std::array<GridTile, gridSizeY>, gridSizeX> GridHandler::CreateGrid() {
	float positionX = 20.f;
	float positionY = 10.f;

	for (int y = 0; y < gridSizeY; y++) {
		for (int x = 0; x < gridSizeX; x++) {
			grid[x][y].positionX = positionX;
			grid[x][y].positionY = positionY;
			grid[x][y].tileIndexX = x;
			grid[x][y].tileIndexY = y;
			grid[x][y].tileType = TileType::Empty;
			positionX += tileSizeX;			
		}
		positionX = 20.f;
		positionY += tileSizeY;
	}
	return grid;
}

std::array<std::array<GridTile, gridSizeY>, gridSizeX> GridHandler::ResetGrid() {
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid[i].size(); k++) {
			grid[i][k].tileType = TileType::Empty;
		}
	}
	return grid;
}

void GridHandler::Draw() {
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid[i].size(); k++) {
			SDL_SetRenderDrawColor(render, 200, 200, 200, 255);
			AABB box = AABB::makeFromPositionSize(grid[i][k].positionX, grid[i][k].positionY, tileSizeX, tileSizeY);
			DrawBox(box);
		}
	}

}
