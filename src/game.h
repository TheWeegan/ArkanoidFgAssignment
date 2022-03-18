#pragma once
#include <memory>
#include <vector>

#include "player.h"
#include "projectile.h"
#include "brick.h"
#include "brickFactory.h"
#include "grid.h"
#include "levelCreator.h"
#include "sprite.h"
#include "spriteSheet.h"

#define ProjectileMax 20
#define BrickMax 8
//#define GridSize 20

extern bool gameOver;
extern bool victory;

extern int screenWidth;
extern int screenHeight;

extern int brickAmount;
extern int bricksDestroyed;

extern std::vector<std::unique_ptr<TheBrick>> allBricks;
extern BrickFactory brickFactory;
extern GridHandler gridHandler;
extern LevelCreator levelCreator;

extern Player player;
extern Projectile projectile;

extern Sprite playerSprite;

extern SpriteSheet ballSpriteSheet;
extern SpriteSheet blockSheet;

extern void CreateLevel(std::array<std::array<GridTile, gridSizeY>, gridSizeX>& grid);
extern void RestartGame();