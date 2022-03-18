#include "collision.h"
#include "bizarreEngine.h"
#include <SDL/SDL.h>

#define PI 3.1415

AABB AABB::makeFromPositionSize(float x, float y, float w, float h) {
	AABB boxCollider;
	boxCollider.xMin = x - w / 2;
	boxCollider.yMin = y - h / 2;

	boxCollider.xMax = x + w / 2;
	boxCollider.yMax = y + h / 2;

	return boxCollider;
}

void DrawCircle(Circle& circle) {
	int resolution = 48;
	float step = (2 * PI) / resolution;

	for (int i = 0; i < resolution; i++) {

		float angle = step * i;
		float x1 = cos(angle);
		float y1 = sin(angle);

		float nextAngle = step * (i + 1);
		float x2 = cos(nextAngle);
		float y2 = sin(nextAngle);

		SDL_RenderDrawLine(
			render,
			x1 * circle.radius + circle.x,
			y1 * circle.radius + circle.y,
			x2 * circle.radius + circle.x,
			y2 * circle.radius + circle.y);

	}
}

void DrawBox(AABB& box) {
	SDL_Rect rect = {
	box.xMin,
	box.yMin,
	box.xMax - box.xMin,
	box.yMax - box.yMin,
	};

	SDL_RenderDrawRect(render, &rect);
}

void FillBox(AABB& box) {
	SDL_Rect rect = {
	box.xMin,
	box.yMin,
	box.xMax - box.xMin,
	box.yMax - box.yMin,
	};

	SDL_RenderFillRect(render, &rect);
}


bool CircleIntersect(Circle& circleA, Circle& circleB) {
	float dx = circleB.x - circleA.x;
	float dy = circleB.y - circleA.y;

	float distanceSquared = dx * dx + dy * dy;
	float distance = sqrt(distanceSquared);

	float radiusSum = circleA.radius + circleB.radius;
	return distance < radiusSum;
}

bool AABBIntersect(AABB& boxA, AABB& boxB) {
	return (
		boxA.xMax > boxB.xMin && 
		boxB.xMax > boxA.xMin &&
		boxA.yMax > boxB.yMin &&
		boxB.yMax > boxA.yMin);
}


float Clamp(float a, float min, float max) {
	if (a < min) {
		return min;
	}
	else if (a > max) {
		return max;
	}
	return a;
}

bool AABBCircleIntersect(AABB& box, Circle& circle) {
	float clampedX = Clamp(circle.x, box.xMin, box.xMax);
	float clampedY = Clamp(circle.y, box.yMin, box.yMax);

	float deltaX = circle.x - clampedX;
	float deltaY = circle.y - clampedY;

	float distanceSquared = deltaX * deltaX + deltaY * deltaY;
	float distance = sqrt(distanceSquared);
	return (distance < circle.radius);
}