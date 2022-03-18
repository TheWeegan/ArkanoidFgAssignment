#include "bizarreEngine.h"

SDL_Window* window;
SDL_Renderer* render;

KeyState keys[SDL_NUM_SCANCODES];
bool GetKey(SDL_Scancode key) {
	return keys[key].state;
}
bool GetKeyPressed(SDL_Scancode key) {
	return keys[key].state && keys[key].changeFrame == frameNumber;
	
}
bool GetKeyReleased(SDL_Scancode key) {
	return !keys[key].state && keys[key].changeFrame == frameNumber;
}

void DrawText(SDL_Texture* textTexture, SDL_Rect* textSrcrect, SDL_Rect textDst) {
	SDL_RenderCopy(render, textTexture, textSrcrect, &textDst);
	SDL_RenderPresent(render);
}

void ClearText(SDL_Surface* textSurface, SDL_Texture* textTexture) {
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

float deltaTime = 0.f;
int frameNumber = 0;