#include "Rect.h"

Rect::Rect(int left, int right, int top, int bottom)
	:
	left(left),
	right(right),
	top(top),
	bottom(bottom)
{
}

Rect::Rect(const Location& loc, int width, int height)
	:
	Rect(loc.x, loc.x + width, loc.y, loc.y + height)
{
}

void Rect::Shrink(int padding)
{
	left += padding;
	right -= padding;
	top += padding;
	bottom -= padding;
}

const Rect Rect::Shrinked(int padding) const
{
	Rect out = *this;
	out.Shrink(padding);
	return out;
}
