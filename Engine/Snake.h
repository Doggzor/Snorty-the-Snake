#pragma once
#include "Keyboard.h"
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		Segment(const Location& loc, Color c);
		void MoveTo(const Location& loc);
		void MoveBy(const Location& d_loc);
		void Draw(const Rect& rect, Color c, Graphics& gfx);
		const Location& GetLoc() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(std::shared_ptr<Board> brd, float speedupFactor);
	void Draw(Graphics& gfx);
	void Update(const Keyboard& kbd, float dt);	
	bool IsDead();
private:
	void Move();
	void Speedup();
	void Grow(int n = 1);
	const Location& GetLoc() const;
	Location GetNextLoc() const;
private:
	std::shared_ptr<Board> board;
	std::vector<std::unique_ptr<Segment>> vSnake;
	Location d_loc{ 0, 0 };
	Color c_head = Colors::Yellow, c_tail = Colors::MakeRGB(0, 100, 0);
	float fMoveIntervalMax = 0.5f, fMoveIntervalMin = 0.05f, fMoveInterval = 0.0f, fSpeedupFactor;
	bool bMoveRdy = true, bDead = false;
};

