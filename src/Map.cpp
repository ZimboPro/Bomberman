//
// Created by Patrick RUSSELL on 2018/08/30.
//

#include <iostream>
#include "Map.hpp"

Map::Map() {}

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

int Map::_currentWorkingLevel = 0;
// std::vector<std::vector<std::vector<char>>> Map::_map; 
Levels Map::_levels;

// = { {_levels.makeMap(0) }, {_levels.makeMap(1)}, {_levels.makeMap(2)} };
std::vector<std::vector<std::vector<char>>> Map::_map = {
		{
				{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '0', '1'},
				{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '3', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '3', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		},
		{
				{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '0', '1'},
				{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '3', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '3', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		},
		{
				{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '0', '1'},
				{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '3', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '3', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
				{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		}
};
