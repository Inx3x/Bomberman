#pragma once

struct Vector3
{
	float x, y;

	Vector3() :x(0), y(0) {}
	Vector3(float _x, float _y) :x(_x), y(_y) {}
};

struct Transform {
	Vector3 position;
	Vector3 scale;
	int index;
};