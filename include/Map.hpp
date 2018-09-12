//
// Created by Patrick RUSSELL on 2018/08/30.
//

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

#include <vector>

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

private:
	static int _currentWorkingLevel;
	static std::vector<std::vector<std::vector<char>>> _map;
};


#endif //BOMBERMAN_MAP_HPP
