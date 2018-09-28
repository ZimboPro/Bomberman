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

void Map::removeAtPosition(int x, int y)
{
	if (_map[y][x] != 'G')
		_map[y][x] = '0';
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
	std::cout << map.size() << std::endl;
	std::cout << map[0].size() << std::endl;
	_map = map;
	std::cout << std::endl;
	std::cout << _map.size() << std::endl;
	std::cout << _map[0].size() << std::endl;
}

void Map::destroyEverything()
{
	for (size_t row = 0; row < _map.size(); row++)
	{
		_map[row].clear();
	}
	_map.clear();
}

Levels Map::_levels;
std::vector<std::vector<char>> Map::_map;
float Map::_playerStartX = 0;
float Map::_playerStartY = 0;
