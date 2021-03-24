#include "Snake.h"

Snake::Snake(std::shared_ptr<Board> brd, float speedupFactor)
	:
	board(brd),
	fSpeedupFactor(speedupFactor)
{
	vSnake.push_back(std::make_unique<Segment>(board->GetLocCenter(), c_head));
	Grow(3);
}

void Snake::Draw(Graphics& gfx)
{
	for (int i = 1; i < (int)vSnake.size(); ++i) {
		Color c = (i - 1) % 4 == 0 ? c_tail * 1.66f : (i - 1) % 4 == 2 ? c_tail : c_tail * 1.33f;
		vSnake[i]->Draw(board->GetRect(vSnake[i]->GetLoc()), c, gfx);
	}
	vSnake[0]->Draw(board->GetRect(vSnake[0]->GetLoc()), c_head, gfx);
}

void Snake::Move()
{
	bDead = board->IsUnsafe(GetNextLoc()); //Crash into border or obstacle
	for (int i = 3; i < (int)vSnake.size() - 1; ++i) { //Crash into own tail
		if (GetNextLoc() == vSnake[i]->GetLoc()) {
			bDead = true;
			break;
		}
	}

	if (!bDead) {
		Location prevloc = vSnake[0]->GetLoc();
		vSnake[0]->MoveBy(d_loc);
		for (int i = 1; i < (int)vSnake.size(); ++i) {
			Location temploc = vSnake[i]->GetLoc();
			vSnake[i]->MoveTo(prevloc);
			prevloc = temploc;
		}
		bMoveRdy = true;
	}
}

void Snake::Update(const Keyboard& kbd, float dt)
{
	if (!bDead) {
		if (bMoveRdy) {
			if (kbd.KeyIsPressed(VK_LEFT))
				if (!d_loc.x) {
					d_loc = { -1, 0 };
					bMoveRdy = false;
				}
			if (kbd.KeyIsPressed(VK_RIGHT))
				if (!d_loc.x) {
					d_loc = { 1, 0 };
					bMoveRdy = false;
				}
			if (kbd.KeyIsPressed(VK_UP))
				if (!d_loc.y) {
					d_loc = { 0, -1 };
					bMoveRdy = false;
				}
			if (kbd.KeyIsPressed(VK_DOWN))
				if (!d_loc.y) {
					d_loc = { 0, 1 };
					bMoveRdy = false;
				}
		}

		fMoveInterval += dt;
		if (fMoveInterval >= fMoveIntervalMax) {
			fMoveInterval -= fMoveIntervalMax;
			if (d_loc != Location(0, 0)) {
				Move();
				if (board->DidConsumeFood(vSnake[0]->GetLoc())) Grow();
				else if (board->DidConsumeDrugs(vSnake[0]->GetLoc())) Speedup();
			}
		}
	}
}

void Snake::Grow(int n)
{
	for (int i = 0; i < n; ++i) {
		Color c = ((int)vSnake.size() - 1) % 4 == 0 ? c_tail * 1.66f : ((int)vSnake.size() - 1) % 4 == 2 ? c_tail : c_tail * 1.33f;
		Location l = vSnake[(int)vSnake.size() - 1]->GetLoc();
		vSnake.push_back(std::make_unique<Segment>(l, c));
	}
}

void Snake::Speedup()
{
	fMoveIntervalMax = std::max(fMoveIntervalMin, fMoveIntervalMax / fSpeedupFactor);
}

const Location& Snake::GetLoc() const
{
	return vSnake[0]->GetLoc();
}

Location Snake::GetNextLoc() const
{
	return vSnake[0]->GetLoc() + d_loc;
}

bool Snake::IsDead()
{
	return bDead;
}

Snake::Segment::Segment(const Location& loc, Color c)
	:
	loc(loc),
	c(c)
{
}

void Snake::Segment::MoveTo(const Location& loc)
{
	this->loc = loc;
}

void Snake::Segment::MoveBy(const Location& d_loc)
{
	loc += d_loc;
}

void Snake::Segment::Draw(const Rect& rect, Color c, Graphics& gfx)
{
	gfx.DrawRect(rect, c);
}

const Location& Snake::Segment::GetLoc() const
{
	return loc;
}
