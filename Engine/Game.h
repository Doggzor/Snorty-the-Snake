/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Numbers.h"
#include "rng.h"
#include "FrameTimer.h"
#include "Vec2.h"
#include "Board.h"
#include "Snake.h"
#include <memory>
#include <fstream>
#include <string>

class Game
{
public:
	enum class State
	{
		Loading,
		Playing,
		Over
	};
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	std::string GetFileContents(std::string fileName) {
		std::ifstream in(fileName);
		std::string out;
		while (in.good()) {
			std::string temp;
			in >> temp;
			out += temp += " ";
		}
		return out;
	}
	int GetNextInt(std::string str, int startPos = 0) {
		std::string temp;
		bool breakFlag = false;
		for (int i = startPos; i < (int)str.size(); ++i) {
			if (str[i] >= '0' && str[i] <= '9') {
				breakFlag = true;
				temp.push_back(str[i]);
			}
			else if (breakFlag) return std::stoi(temp);
		}
		return -1;
	}
	int GetNextInt(std::string str, std::string searchAfterThis) {
		return GetNextInt(str, (int)str.find(searchAfterThis) + (int)searchAfterThis.size());
	}
	float GetNextFloat(std::string str, int startPos = 0) {
		std::string temp;
		bool breakFlag = false;
		bool decimal = false;
		bool decimalStart = false;
		for (int i = startPos; i < (int)str.size(); ++i) {
			if (str[i] >= '0' && str[i] <= '9') {
				decimalStart = true;
				temp.push_back(str[i]);
			}
			else if (str[i] == '.' && decimalStart && !decimal) {
				temp.push_back('.');
				decimal = true;
				breakFlag = true;
			}
			else if (breakFlag)
				return std::stof(temp);
		}
		return -1.0f;
	}
	float GetNextFloat(std::string str, std::string searchAfterThis) {
		return GetNextFloat(str, (int)str.find(searchAfterThis) + (int)searchAfterThis.size());
	}
	void InitializeFromString(std::string str) {
		nTileSize = GetNextInt(str, "[Tile Size]");
		nDrugs = GetNextInt(str, "[Drug Amount]");
		nFood = GetNextInt(str, "[Food Amount]");
		nColumns = GetNextInt(str, "[Board Size]");
		std::string temp = "[Board Size]";
		int i = (int)str.find(temp) + (int)temp.size();
		temp.clear();
		bool ignoring = true, ignoreFlag = false;
		for (; i < (int)str.size(); ++i) {
			if (!ignoring) {
				if (str[i] >= '0' && str[i] <= '9')
					temp.push_back(str[i]);
				else break;
			}
			else {
				if (str[i] >= '0' && str[i] <= '9')
					ignoreFlag = true;
				else if (ignoreFlag)
					ignoring = false;
			}
		}
		nRows = std::stoi(temp);
		fSpeedUpFactor = GetNextFloat(str, "[Speedup Rate]");
	}
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
    FrameTimer ft;
	/********************************/
	std::shared_ptr<Board> brd;
	std::unique_ptr<Snake> snake;
	State state = State::Loading;

	int nColumns = 0, nRows = 0, nTileSize = 0, nDrugs = 0, nFood = 0;
	float fSpeedUpFactor = 0.0f;

	//Maybe add an option to turn off obstacle spawning and to adjust obstacle spawn rate
};