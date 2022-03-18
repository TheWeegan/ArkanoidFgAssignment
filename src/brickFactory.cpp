#include "brickFactory.h"
#include "game.h"

std::unique_ptr<TheBrick> BrickFactory::CreateBrick(float x, float y, float w, float h, BrickType brickType) {
	std::unique_ptr<TheBrick> brick = std::make_unique<TheBrick>();
	brick->SetValues(x, y, w, h, brickType);
	return brick;
}

void TheBrick::SetValues(float x, float y, float w, float h, BrickType brickType) {
	brick.alive = true;
	brick.brickType = brickType;
	brick.x = x;
	brick.y = y;	
	brick.w = w;
	brick.h = h;

	switch (brickType) {
	case BrickType::BlueBrick: {
		brick.r = 0.f;
		brick.g = 0.f;
		brick.b = 255.f;
		brick.a = 255.f;
		break;
	}
	case BrickType::GreenBrick: {
		brick.r = 0.f;
		brick.g = 255.f;
		brick.b = 0.f;
		brick.a = 255.f;
		break;
	}
	case BrickType::YellowBrick: {
		brick.r = 255.f;
		brick.g = 255.f;
		brick.b = 0.f;
		brick.a = 255.f;
		break;
	}
	case BrickType::RedBrick: {
		brick.r = 255.f;
		brick.g = 0.f;
		brick.b = 0.f;
		brick.a = 255.f;
		break;
	}
	case BrickType::MetalBrick: {
		brick.r = 100.f;
		brick.g = 100.f;
		brick.b = 100.f;
		brick.a = 255.f;
		break;
	}
	default:
		break;
	}
}

void TheBrick::Draw() {
	if (!brick.alive) {
		return;
	}
	SDL_SetRenderDrawColor(render, brick.r, brick.g, brick.b, brick.a);
	AABB box = AABB::makeFromPositionSize(brick.x, brick.y, brick.w, brick.h);
	FillBox(box);
}

const BrickStruct TheBrick::GetBrick() const {
	return brick;
}

void TheBrick::TakeDamage() {
	switch (brick.brickType) {
	case BrickType::BlueBrick: {
		brick.alive = false;
		bricksDestroyed++;
		if (bricksDestroyed >= brickAmount) {
			victory = true;
		}
		break;
	}
	case BrickType::GreenBrick: {
		brick.r = 0.f;
		brick.g = 0.f;
		brick.b = 255.f;
		brick.a = 255.f;
		brick.brickType = BrickType::BlueBrick;
		break;
	}
	case BrickType::YellowBrick: {
		brick.r = 0.f;
		brick.g = 255.f;
		brick.b = 0.f;
		brick.a = 255.f;
		brick.brickType = BrickType::GreenBrick;
		break;
	}
	case BrickType::RedBrick: {
		brick.r = 255.f;
		brick.g = 255.f;
		brick.b = 0.f;
		brick.a = 255.f;
		brick.brickType = BrickType::YellowBrick;
		break;
	}
	case BrickType::MetalBrick: {
		break;
	}
	default:
		break;
	}

}
