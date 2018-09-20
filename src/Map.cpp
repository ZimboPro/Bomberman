//
// Created by Patrick RUSSELL on 2018/08/30.
//

#include <iostream>
#include "Map.hpp"

Map::Map() {}

Map::Map(Map const & src) 
{
	*this = src;
}

Map::~Map() {}

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

void Map::readInRandomMap(int seed)
{
	_map.push_back(_levels.makeMap(seed));
}

int Map::_currentWorkingLevel = 0;
Levels Map::_levels;
std::vector<std::vector<std::vector<char>>> Map::_map;