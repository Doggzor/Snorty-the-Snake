#include "Board.h"
using namespace std;

Board::Board(int columns, int rows, int tileSize, int drugs, int food, Graphics& gfx)
	:
	nColumns(columns),
	nRows(rows),
	nTileSize(tileSize),
	nDrugs(drugs),
	nFood(food),
	rect(gfx.ScreenWidth / 2 - (nColumns * nTileSize) / 2 - nPadding, gfx.ScreenWidth / 2 + (nColumns * nTileSize) / 2 + nPadding,
		gfx.ScreenHeight / 2 - (nRows * nTileSize) / 2 - nPadding, gfx.ScreenHeight / 2 + (nRows * nTileSize) / 2 + nPadding)
{
	for (int i = 0; i < nColumns * nRows; ++i) {
		Location l(i % nColumns, i / nColumns);
		vTile.push_back(std::make_unique<Tile>(l, GetRect(l), Tile::Type::Empty));
	}
	for (int i = 0; i < drugs; ++i) {
		SpawnObject(Tile::Type::Drugs);
	}
	for (int i = 0; i < food; ++i) {
		SpawnObject(Tile::Type::Food);
	}
}

void Board::Draw(Graphics& gfx)
{
	gfx.DrawRectEmpty(rect, nThickness, c);
	for (auto i = 0; i < (int)vTile.size(); ++i) {
		vTile[i]->Draw(gfx);
	}
}

void Board::SpawnObject(Tile::Type objType)
{
	while (true) {
		int i = rng::rdm_int(0, (int)vTile.size() - 1);
		if (vTile[i]->GetType() == Tile::Type::Empty) {
			vTile[i]->SetType(objType);
			break;
		}
	}
}

void Board::Update(float dt)
{
	fObsSpawnInterval += dt;
	if (fObsSpawnInterval >= fObsSpawnIntervalMax) {
		fObsSpawnInterval -= fObsSpawnIntervalMax;
		SpawnObject(Tile::Type::Obstacle);
	}
}

Location Board::GetScreenLoc(const Location& gridLoc) const
{
	return Location(rect.left + gridLoc.x * nTileSize, rect.top + gridLoc.y * nTileSize);
}

Location Board::GetLocCenter() const
{
	return Location(nColumns / 2, nRows / 2);
}

int Board::GetTileSize() const
{
	return nTileSize;
}

int Board::GetTileIndex(const Location& loc) const
{
	return loc.y * nColumns + loc.x;
}

const Rect Board::GetRect(const Location& loc) const
{
	return Rect(Location(rect.left + nPadding, rect.top + nPadding) + loc * nTileSize, nTileSize, nTileSize).Shrinked(nPadding);
}

bool Board::IsUnsafe(const Location& loc) const
{
	return ((loc.x < 0 || loc.x > nColumns - 1 || loc.y < 0 || loc.y > nRows - 1) //Location out of bounds
		|| GetTileType(loc) == Tile::Type::Obstacle); // Location occupied by obstacle
}

bool Board::DidConsumeFood(const Location& loc)
{
	if (GetTileType(loc) == Tile::Type::Food) {
		vTile[GetTileIndex(loc)]->SetType(Tile::Type::Empty);
		SpawnObject(Tile::Type::Food);
		return true;
	}
	return false;
}

bool Board::DidConsumeDrugs(const Location& loc)
{
	if (GetTileType(loc) == Tile::Type::Drugs) {
		vTile[GetTileIndex(loc)]->SetType(Tile::Type::Empty);
		return true;
	}
	return false;
}

Board::Tile::Type Board::GetTileType(const Location& loc) const
{
	return vTile[GetTileIndex(loc)]->GetType();
}

Board::Tile::Tile(const Location& loc, const Rect& rect, Type type)
	:
	eType(type),
	loc(loc),
	rect(rect)
{
}

void Board::Tile::Draw(Graphics& gfx)
{
	
	switch (eType) {
	case Type::Drugs:
		c = Colors::MakeRGB(100, 0, 100);
		break;
	case Type::Food:
		c = Colors::MakeRGB(200, 50, 50);
		break;
	case Type::Obstacle:
		c = Colors::Gray;
		break;
	case Type::Empty:
	default:
		c = Colors::Black;
		break;
	}
	gfx.DrawRect(rect, c);
}

const Board::Tile::Type& Board::Tile::GetType() const
{
	return eType;
}

void Board::Tile::SetType(Type type)
{
	eType = type;
}

const Location& Board::Tile::GetLoc() const
{
	return loc;
}
