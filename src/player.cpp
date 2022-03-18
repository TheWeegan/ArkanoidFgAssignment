#include "SDL/SDL.h"
#include "player.h"
#include "bizarreEngine.h"
#include "game.h"

void Player::Update() {
	if (GetKey(SDL_SCANCODE_D) && x < screenWidth) {
		x += movementSpeed * deltaTime;
	}
	if (GetKey(SDL_SCANCODE_A) && x > 0) {
		x -= movementSpeed * deltaTime;
	}
	
	if(GetKeyPressed(SDL_SCANCODE_SPACE) && !projectile.alive) {
		projectile.alive = true;
		
		projectile.velocityX = -50.f;
		projectile.velocityY = -200.f;
	}
}

void Player::Draw() {
	SDL_SetRenderDrawColor(render, 0, 50, 25, 255);
	SDL_Rect rect = { (int)x - player.w / 2,(int)y - player.h / 2, (int)w, (int)h};
	SDL_RenderFillRect(render, &rect);

	//playerSprite.DrawCentered((int)x, (int)y);
}