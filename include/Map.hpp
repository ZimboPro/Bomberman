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

	std::vector<char> operator[](int i);
	int getLevel();
	void levelUp();

private:
	std::vector<std::vector<std::vector<char>>> _map;
	int _currentWorkingLevel;
};


#endif //BOMBERMAN_MAP_HPP