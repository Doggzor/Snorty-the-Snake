/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::string config = GetFileContents("config.txt");
	InitializeFromString(config);
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = ft.Mark();

	switch (state) {
	case State::Loading:
		brd = std::make_unique<Board>(nColumns, nRows, nTileSize, nDrugs, nFood, gfx);
		snake = std::make_unique<Snake>(brd, fSpeedUpFactor);
		state = State::Playing;
		break;
	case State::Playing:
		brd->Update(dt);
		snake->Update(wnd.kbd, dt);
		if (snake->IsDead()) state = State::Over;
		break;
		case State::Over:
			if (wnd.kbd.KeyIsPressed(VK_ESCAPE)) state = State::Loading;
	}
}

void Game::ComposeFrame()
{
	switch (state) {
	case State::Loading:
		break;
	case State::Playing:
	case State::Over:
		brd->Draw(gfx);
		snake->Draw(gfx);
		break;
	}
}

