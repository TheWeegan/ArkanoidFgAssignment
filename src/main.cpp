#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "bizarreEngine.h"
#include "spriteSheet.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "grid.h"

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(1);

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	blockSheet.Load("res/blockSheet.png", 40, 20);

	playerSprite.Load("res/playerSprite.png");	
	playerSprite.w = player.w;
	playerSprite.h = player.h;

	ballSpriteSheet.Load("res/carrotChanSheet.png", 32, 64);

	TTF_Font* font = TTF_OpenFont("res/roboto.ttf", 24);
	SDL_Surface* gameOverTextSurface = TTF_RenderText_Solid(font, "Maaan, you suck bawls bruh", {255, 255, 255, 255});
	SDL_Texture* gameOverTextTexture = SDL_CreateTextureFromSurface(render, gameOverTextSurface); 	
	
	SDL_Surface* victoryTextSurface = TTF_RenderText_Solid(font, "Eh, it's okay", {255, 255, 255, 255});
	SDL_Texture* victoryTextTexture = SDL_CreateTextureFromSurface(render, victoryTextSurface);

	SDL_Surface* startTextSurface = TTF_RenderText_Solid(font, "Press space to start", { 255, 255, 255, 255 });
	SDL_Texture* startTextTexture = SDL_CreateTextureFromSurface(render, startTextSurface);

	std::array<std::array<GridTile, gridSizeY>, gridSizeX> theGrid = gridHandler.CreateGrid();
	CreateLevel(theGrid);

	Uint64 previous_ticks = SDL_GetPerformanceCounter();
	bool running = true;
	while (running) {
		frameNumber++;

		Uint64 ticks = SDL_GetPerformanceCounter();		
		Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks;
		deltaTime = (float)delta_ticks / SDL_GetPerformanceFrequency();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				running = false;
				break;
			}
			case SDL_KEYDOWN: {
				if (event.key.repeat) { 
					break; 
				}
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE) {
					running = false;
				}
				keys[scancode].state = true;
				keys[scancode].changeFrame = frameNumber;				
				break;
			}
			case SDL_KEYUP: {
				int scancode = event.key.keysym.scancode;
				keys[scancode].state = false;
				keys[scancode].changeFrame = frameNumber;				
				break;
			}
			}
		}

		if (gameOver) {
			SDL_Rect gameOverTextDst = { screenWidth / 3, screenHeight / 2, gameOverTextSurface->w, gameOverTextSurface->h };
			DrawText(gameOverTextTexture, NULL, gameOverTextDst);
			if (GetKeyPressed(SDL_SCANCODE_SPACE)) {
				allBricks.clear();
				theGrid = gridHandler.ResetGrid();
				RestartGame();
				CreateLevel(theGrid);
			}
			continue;
		} else if (victory) {
			SDL_Rect victoryTextDst = { screenWidth / 3, screenHeight / 2, victoryTextSurface->w, victoryTextSurface->h };
			DrawText(victoryTextTexture, NULL, victoryTextDst);
			if (GetKeyPressed(SDL_SCANCODE_SPACE)) {
				allBricks.clear();
				theGrid = gridHandler.ResetGrid();
				RestartGame();
				CreateLevel(theGrid);
			}
			continue;
		}

		SDL_SetRenderDrawColor(render, 25, 25, 40, 255);
		SDL_RenderClear(render);
		if (!projectile.alive) {
			SDL_Rect startTextDst = { screenWidth / 3, screenHeight / 2, startTextSurface->w, startTextSurface->h };
			DrawText(startTextTexture, NULL, startTextDst);
		}

		for (int i = 0; i < allBricks.size(); i++) {
			allBricks[i]->Draw();
		}
		gridHandler.Draw();

		player.Update();
		player.Draw();

		projectile.Update();
		projectile.Draw();

		SDL_RenderPresent(render);
		SDL_Delay(16);
	}
}