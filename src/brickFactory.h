#pragma once
#include <memory>

#include "bizarreEngine.h"
#include "collision.h"

enum class BrickType {
	BlueBrick,
	GreenBrick,
	YellowBrick,
	RedBrick,
	MetalBrick,
	Count
};

struct BrickStruct {
	bool alive = true;

	BrickType brickType;

	float x = 0;
	float y = 0;

	float w = 40.f;
	float h = 20.f;

	int r = 255;
	int g = 255;
	int b = 255;
	int a = 255;
};

class TheBrick {
public:
	TheBrick() {};
	~TheBrick() {};
	
	void SetValues(float x, float y, float w, float h, BrickType brickType);
	void Draw();

	const BrickStruct GetBrick() const;
	void TakeDamage();

private:
	BrickStruct brick;
};

class BrickFactory {
public:
	BrickFactory() {}
	~BrickFactory() {}

	std::unique_ptr<TheBrick> CreateBrick(float x, float y, float w, float h, BrickType brickType);
};