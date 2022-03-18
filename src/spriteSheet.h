#pragma once
#include <SDL/SDL_image.h>

struct SpriteSheet {
	void Load(const char* path, int width, int height);
	void Draw(int spriteIndex, int x, int y);


	SDL_Texture* texture;
	int w;
	int h;
};

