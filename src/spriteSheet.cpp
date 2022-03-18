#include "spriteSheet.h"
#include "bizarreEngine.h"

void SpriteSheet::Load(const char* path, int width, int height) {
	texture = IMG_LoadTexture(render, path);
	w = width;
	h = height;
}

void SpriteSheet::Draw(int spriteIndex, int x, int y) {
	SDL_Rect source = { spriteIndex * w, 0, w, h };
	SDL_Rect destination = { x, y, w, h };

	SDL_RenderCopy(render, texture, &source, &destination);
}
