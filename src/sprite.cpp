#include "sprite.h"
#include "bizarreEngine.h"

void Sprite::Load(const char* path) {
	texture = IMG_LoadTexture(render, path);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void Sprite::Draw(int x, int y) {
	SDL_Rect destination = { x, y, w, h };
	SDL_RenderCopy(render, texture, NULL, &destination);
}

void Sprite::DrawCentered(int x, int y) {
	SDL_Rect destination = { x - w / 2, y - h / 2, w, h };
	SDL_RenderCopy(render, texture, NULL, &destination);
}


