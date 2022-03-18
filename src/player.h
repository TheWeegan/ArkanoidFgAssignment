#pragma once
#include <random>

struct Player {
	float x = 400.f;
	float y = 550.f;
	float w = 100.f;
	float h = 20.f;
	float movementSpeed = 400;

	void Update();
	void Draw();

	std::random_device randomSeed;
};