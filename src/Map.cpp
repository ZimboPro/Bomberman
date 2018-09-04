//
// Created by Patrick RUSSELL on 2018/08/30.
//

#include "Map.hpp"

Map::Map() {}

Map::~Map() {}

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

int Map::mapHeight()
{
	return _map.size();
}

int Map::mapWidth()
{
	return _map[0].size();
}
std::vector<std::vector<char>> Map::_map = {
			{'1', '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','3','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1', '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
			};
			
int Map::_currentWorkingLevel = 0;
