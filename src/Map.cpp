//
// Created by Patrick RUSSELL on 2018/08/30.
//

#include <iostream>
#include "Map.hpp"

Map::Map() = default;

Map::Map(Map const & src) 
{
	*this = src;
}

Map::~Map() = default;

char Map::at(int x, int y)
{
	return _map[_currentWorkingLevel][y][x];
}

int Map::getLevel()
{
	return _currentWorkingLevel;
}

void Map::levelUp()
{
	_currentWorkingLevel++;
}

size_t Map::height()
{
	return _map[_currentWorkingLevel].size();
}

size_t Map::width()
{
	return _map[_currentWorkingLevel][0].size();
}

void Map::printMap()
{
	for (size_t y = 0; y < _map[_currentWorkingLevel].size(); y++)
	{
		for (size_t x = 0; x < _map[_currentWorkingLevel][0].size(); x++)
			std::cout << _map[_currentWorkingLevel][y][x];

		std::cout << std::endl;
	}
}

std::vector<std::vector<std::vector<char >>> Map::getLevelHolder()
{
	return _map;
}

void Map::levelDown()
{
	if (_currentWorkingLevel > 0)
		_currentWorkingLevel--;
}

float Map::getPlayerStartX()
{
	return _playerStartX;
}

float Map::getPlayerStartY()
{
	return _playerStartY;
}

void Map::setPlayerStart(float x, float y)
{
	_playerStartX = x;
	_playerStartY = y;
}

void Map::readInRandomMap(int seed)
{
//	if (seed == 0)
//	{
//		_map.push_back(std::vector<std::vector<char> > {
//				{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//				{'0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','3','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','7','0','1','0'},
//				{'0','1','0','0','0','0','0','G','0','0','0','0','0','0','1','0'},
//				{'0','1','0','2','0','0','0','0','0','0','6','0','0','0','1','0'},
//				{'0','1','0','2','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','6','0','7','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','2','2','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','6','0','7','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','0','0','0','0','0','0','0','0','0','0','0','0','1','0'},
//				{'0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0'},
//				{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//		});
//	}
	_map.push_back(_levels.makeMap(seed));
}

int Map::_currentWorkingLevel = 0;
Levels Map::_levels;
std::vector<std::vector<std::vector<char>>> Map::_map;
float Map::_playerStartX = 0;
float Map::_playerStartY = 0;
