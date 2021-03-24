#pragma once
#include "Location.h"
struct Rect
{
	Rect() = default;
	Rect(int left, int right, int top, int bottom);
	Rect(const Location& loc, int width, int height);
	void Shrink(int padding);
	const Rect Shrinked(int padding) const;
	int left, right, top, bottom;
};

