#pragma once
#include <SDL/SDL_image.h>

struct Sprite {
	void Load(const char* path);
	void Draw(int x, int y);
	void DrawCentered(int x, int y);

	SDL_Texture* texture;
	int w;
	int h;
};
