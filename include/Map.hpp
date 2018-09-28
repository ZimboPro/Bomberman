//
// Created by Patrick RUSSELL on 2018/08/30.
//

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

#include <vector>
#include "map_generation/Levels.hpp"

class Map
{
public:
	Map();
	Map(Map const & src);
	~Map();

	static char at(int x, int y);
	static int getLevel();
	static size_t width();
	static size_t height();
	static size_t size();
	static void printMap();
	static void readInRandomMap(int seed);
	static Levels	_levels;
	static std::vector<std::vector<char>> getLevelHolder();
	static void setPlayerStart(float x, float y);
	static float getPlayerStartX();
	static float getPlayerStartY();
	static void	setMap(std::vector<std::vector<char>> map);
	static void removeAtPosition(int x, int y);
	static void destroyEverything();

private:
	static std::vector<std::vector<char>> _map;
	static float _playerStartX;
	static float _playerStartY;

};

#endif //BOMBERMAN_MAP_HPP
