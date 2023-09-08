#pragma once

// ---------
// Includes
// ---------
#include "raylib.h"
#include <string>
#include <iostream>

// --------
// Classes
// --------
class Init
{
public:
	void game();
};

// --------
// Structs
// --------
struct Ball
{
	int x, y;
	float radius;
	float speedX, speedY;

	int defX, defY;
	float defSpeedX, defSpeedY;

	Color color;
	void Draw()
	{
		DrawCircle(x, y, radius, color);
	}
};

struct Paddle
{
	int x, y;
	int width, height;
	int speed;

	int defX, defY;
	int defSpeed;

	Color color;
	Rectangle GetPos()
	{
		return Rectangle{ float(x) - width / 2, float(y) - height / 2, float(width), float(height) };
	}

	void Draw()
	{
		DrawRectangleRec(GetPos(), color);
	}
};