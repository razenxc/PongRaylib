#pragma once

// ---------
// Includes
// ---------
#include "raylib.h"
#include <string>
#include <iostream>

// --------------------
// Functions prototype
// --------------------
void game();

// --------
// Classes
// --------
class Counter
{
private:
	int count = 0;
public:
	void add_count()
	{
		count++;
	}
	void clear_count()
	{
		count = 0;
	}
	int get_count()
	{
		return count;
	}
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