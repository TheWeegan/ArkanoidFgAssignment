#include "brick.h"
#include "collision.h"
#include "bizarreEngine.h"

void Brick::Draw() {
	if (!alive) {
		return;
	}

	SDL_SetRenderDrawColor(render, 200, 200, 50, 255);
	AABB box = AABB::makeFromPositionSize(x, y, w, h);
	DrawBox(box);
}
