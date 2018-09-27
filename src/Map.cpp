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
	return _map[y][x];
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
	return _map.size();
}

size_t Map::width()
{
	return _map[0].size();
}

size_t Map::size()
{
	return _map.size();
}

void Map::printMap()
{
	for (size_t y = 0; y < _map.size(); y++)
	{
		for (size_t x = 0; x < _map[0].size(); x++)
			std::cout << _map[y][x];

		std::cout << std::endl;
	}
}

std::vector<std::vector<char >> Map::getLevelHolder()
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
	setMap(_levels.makeMap(seed));
}

void Map::setMap(std::vector<std::vector<char>> map)
{
	_map = map;
}

void Map::destroyEverything()
{
	for (size_t row = 0; row < _map.size(); row++)
	{
		_map[row].clear();
	}
	_map.clear();
}

int Map::_currentWorkingLevel = 0;
Levels Map::_levels;
std::vector<std::vector<char>> Map::_map;
float Map::_playerStartX = 0;
float Map::_playerStartY = 0;
