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
		while (projectile.velocityX > -25.f && projectile.velocityX < 25.f) {
			std::default_random_engine randomEngine{ randomSeed() };
			std::uniform_real_distribution<float> randomDist(-100.f, 100.f);
			projectile.velocityX = randomDist(randomEngine);
		}
		projectile.velocityY = -200.f;
	}
}

void Player::Draw() {
	playerSprite.DrawCentered((int)x, (int)y);
}