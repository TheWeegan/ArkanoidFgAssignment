#pragma once

struct Circle {
	float x;
	float y;
	float radius;
};

struct AABB {
	static AABB makeFromPositionSize(float x, float y, float w, float h);

	float xMin;
	float xMax;

	float yMin;
	float yMax;
};

void DrawCircle(Circle& circle);

void DrawBox(AABB& box);

void FillBox(AABB& box);

bool CircleIntersect(Circle& circleA, Circle& circleB);

bool AABBIntersect(AABB& boxA, AABB& boxB);

bool AABBCircleIntersect(AABB& box, Circle& circle);