#include "game.h"

bool gameOver = false;
bool victory = false;

int screenWidth = 800;
int screenHeight = 600;


int brickAmount = 0;
int bricksDestroyed = 0;

std::vector<std::unique_ptr<TheBrick>> allBricks;
BrickFactory brickFactory;

GridHandler gridHandler;
LevelCreator levelCreator;

Player player;
Projectile projectile;

Sprite playerSprite;

SpriteSheet ballSpriteSheet;
SpriteSheet blockSheet;

void CreateLevel(std::array<std::array<GridTile, gridSizeY>, gridSizeX>& grid) {
	const unsigned int brickTypeAmount = (int)BrickType::Count;
	
	const unsigned int currentMinPosX = gridSizeX / brickTypeAmount;
	const unsigned int currentMaxPosX = gridSizeX - brickTypeAmount;

	unsigned int currentMinPosY = gridSizeY / brickTypeAmount;
	unsigned int currentMaxPosY = gridSizeY - brickTypeAmount;

	levelCreator.DrunkardWalk(grid, BrickType::BlueBrick, currentMinPosX, currentMaxPosX, currentMaxPosY, currentMaxPosY + currentMinPosY);
	currentMaxPosY -= currentMinPosY;
	levelCreator.DrunkardWalk(grid, BrickType::GreenBrick, currentMinPosX, currentMaxPosX, currentMinPosY, currentMinPosY + currentMaxPosY);
	currentMaxPosY -= currentMinPosY;
	levelCreator.DrunkardWalk(grid, BrickType::YellowBrick, currentMinPosX, currentMaxPosX, currentMinPosY, currentMinPosY + currentMaxPosY);
	levelCreator.DrunkardWalk(grid, BrickType::RedBrick, currentMinPosX, currentMaxPosX, 0, currentMaxPosY);

}

void RestartGame() {
	projectile.alive = false;
	victory = false;
	gameOver = false;
	bricksDestroyed = 0;
	player.x = screenWidth / 2;
}
