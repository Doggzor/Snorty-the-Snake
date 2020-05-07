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
}

void Game::ComposeFrame()
{
}

void Game::drawHPbar(float maxWidth, float height, float maxHealth, float health, const Vec2& topleft)
{
    //Colors (goes slowly from RED at very low HP to YELLOW at around half HP to GREEN at full HP)
    //Green ( equal to 255 if HP is 50% or over, then starts decreasing as HP decreases)
    int G = (int)((health / (maxHealth / 2.0f)) * 255.0f);
    if (G > 255) G = 255;
    else if (G < 0) G = 0;
    //Red ( equal to 0 if HP is full then starts increasing as HP decreases, max value is 255 at 50% HP or lower)
    int R = (int)((maxHealth - health) / (maxHealth / 2.0f) * 255.0f);
    if (R > 255) R = 255;
    else if (R < 0) R = 0;
    //Position
    const int x = (int)topleft.x;
    const int y = (int)topleft.y;
    //Width
    const float fWidth = maxWidth * (health / maxHealth);
    int nWidth = (int)fWidth;
    const int nHeight = (int)height;
    if (fWidth < 1.0f && fWidth > 0.0f) nWidth = 1;
    gfx.DrawRectDim(x, y, nWidth, nHeight, Colors::MakeRGB(R, G, 0));
}