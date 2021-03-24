#pragma once
#include "Graphics.h"
#include "Rect.h"
#include <vector>
#include <memory>
#include "Location.h"
#include "rng.h"

class Board
{
private:
	class Tile
	{
	public:
		enum class Type
		{
			Empty,
			Food,
			Drugs,
			Obstacle
		};

		Tile(const Location& loc, const Rect& rect, Type type);
		void Draw(Graphics& gfx);
		const Type& GetType() const;
		void SetType(Type type);
		const Location& GetLoc() const;
	private:
		Type eType = Type::Empty;
		Location loc;
		Rect rect;
		Color c;
	};
public:
	Board(int columns, int rows, int tileSize, int drugs, int food, Graphics& gfx);
	void Draw(Graphics& gfx);	
	void Update(float dt);
	Location GetLocCenter() const;
	const Rect GetRect(const Location& loc) const; 
	bool IsUnsafe(const Location& loc) const;
	bool DidConsumeFood(const Location& loc);
	bool DidConsumeDrugs(const Location& loc);
private:
	Location GetScreenLoc(const Location& gridLoc) const;
	void SpawnObject(Tile::Type objType);
	Tile::Type GetTileType(const Location& loc) const;
	int GetTileSize() const;
	int GetTileIndex(const Location& loc) const;
private:
	int nRows, nColumns, nTileSize, nDrugs, nFood, nFoodCnt = 0;
	float fObsSpawnIntervalMax = 5.0f, fObsSpawnInterval = 0.0f;
	static constexpr int nThickness = -5;
	Rect rect;
	Color c = Colors::Gray;
	std::vector<std::unique_ptr<Tile>> vTile;

public:
	static constexpr int nPadding = 2;
};

