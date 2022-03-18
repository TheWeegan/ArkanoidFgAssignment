#include "projectile.h"
#include "bizarreEngine.h"
#include "collision.h"
#include "game.h"
#include "brickFactory.h"

float sign(float a) { return  a > 0.f ? 1.f : -1.f; }

void Projectile::Update() {
	if (!alive) {
		x = player.x;
		y = player.y - player.h / 2;
		return;
	}
	if (!step(velocityX * deltaTime, 0.f)) {
		velocityX = -velocityX + sign(-velocityX) *  5.f;
	}	
	if (!step(0.f, velocityY * deltaTime)) {
		velocityY = -velocityY + sign(-velocityY) * 5.f;
	}
}

void Projectile::Draw() {
	if (projectile.alive) {
		animTime += deltaTime;
	}
	ballSpriteSheet.Draw((int)(animTime * 7) % 2, x - (w / 2), y - r);
}

bool Projectile::step(float deltaX, float deltaY) {
	Circle circle = { x + deltaX, y + deltaY, r };
	for (int i = 0; i < allBricks.size(); i++) {
		TheBrick& brick = *allBricks[i];
		if (!brick.GetBrick().alive) {
			continue;
		}
		AABB box = AABB::makeFromPositionSize(brick.GetBrick().x, brick.GetBrick().y, brick.GetBrick().w, brick.GetBrick().h);
		if (AABBCircleIntersect(box, circle)) {
			brick.TakeDamage();
			return false;
		}
	}
	if (deltaY > 0) {
		AABB playerBox = AABB::makeFromPositionSize(player.x, player.y, player.w, player.h);
		if (AABBCircleIntersect(playerBox, circle)) {
			return false;
		}
	}
	if (x + deltaX < 0 || x + deltaX >= screenWidth || 
		y + deltaY < 0) {
		return false;
	}
	else if (y + deltaY >= screenHeight) {
		gameOver = true;
		alive = false;
	}
	x += deltaX;
	y += deltaY;
	return true;
}
