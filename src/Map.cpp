//
// Created by Patrick RUSSELL on 2018/08/30.
//

#include "Map.hpp"

Map(): _currentWorkingLevel(0) {}

~Map();

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
