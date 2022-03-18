#pragma once

struct Projectile {
	bool alive = false;
	float x;
	float y;
	float w = 16.f;
	float h = 32.f;
	float r = 4.f;

	float velocityX;
	float velocityY;

	float animTime = 0.f;

	void Update();
	void Draw();

	bool step(float deltaX, float deltaY);
};