#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_scancode.h>

extern SDL_Window* window;
extern SDL_Renderer* render;

struct KeyState {
	bool state = false;
	int changeFrame = 0;
};

extern KeyState keys[SDL_NUM_SCANCODES];
extern bool GetKey(SDL_Scancode key);
extern bool GetKeyPressed(SDL_Scancode key);
extern bool GetKeyReleased(SDL_Scancode key);

void DrawText(SDL_Texture* textTexture, SDL_Rect* textSrcrect, SDL_Rect textDst);
void ClearText(SDL_Surface* textSurface, SDL_Texture* textTexture);


extern float deltaTime;
extern int frameNumber;