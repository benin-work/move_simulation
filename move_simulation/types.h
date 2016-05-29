#pragma once

struct Vector2D;

typedef Vector2D Vector;

struct Vector2D
{
	Vector2D(): x(0), y(0)
	{			
	}

	Vector2D(double ix, double iy = 0) : x(ix), y(iy)
	{
	}

	double x;
	double y;
};

