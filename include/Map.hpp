//
// Created by Patrick RUSSELL on 2018/08/30.
//

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

#include <vector>
#include "../Map_Gen/Levels.hpp"

class Map
{
public:
	Map();
	~Map();

	static char at(int x, int y);
	static int getLevel();
	static void levelUp();
	static size_t width();
	static size_t height();
	static void printMap();
	static void readInRandomMap(int seed);

private:
	static int _currentWorkingLevel;
	static std::vector<std::vector<std::vector<char>>> _map;
	static Levels	_levels;
};

#endif //BOMBERMAN_MAP_HPP
