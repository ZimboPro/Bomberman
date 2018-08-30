//
// Created by Patrick RUSSELL on 2018/08/30.
//

#include "Map.hpp"

std::vector<char> Map::operator[](int i)
{
	return _map[_currentWorkingLevel][i];
}