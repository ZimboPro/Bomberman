//
// Created by Patrick RUSSELL on 2018/08/30.
//

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

#include <vector>

class Map
{
public:
	static Map();
	static ~Map();

	static char at(int x, int y);
	static int getLevel();
	static void levelUp();
	static int mapWidth();
	static int mapHeight();

private:
	static std::vector<std::vector<char>> _map = {
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
	static int _currentWorkingLevel;
};


#endif //BOMBERMAN_MAP_HPP
