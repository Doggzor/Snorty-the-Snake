#pragma once
struct Location
{
	Location() = default;
	Location(int x, int y)
		:
		x(x),
		y(y)
	{}
	bool operator==(const Location& loc) {
		return x == loc.x && y == loc.y;
	}
	bool operator!=(const Location& loc) {
		return x != loc.x || y != loc.y;
	}
	Location operator+ (const Location&  delta_loc) const {
		return { x + delta_loc.x, y + delta_loc.y };
	}
	Location& operator+= (const Location& delta_loc) {
		return *this = *this + delta_loc;
	}
	Location operator* (int n) const {
		return { x * n, y * n };
	}

	int x, y;
};
