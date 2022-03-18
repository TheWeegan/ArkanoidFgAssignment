#pragma once

struct Projectile {
	bool alive = false;
	float x;
	float y;

	float velocityX;
	float velocityY;

	void Update();
	void Draw();

	bool step(float deltaX, float deltaY);
};