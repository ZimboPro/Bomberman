//
// Created by Patrick RUSSELL on 2018/09/03.
//

#include "ObjectFactory.hpp"
#include "Map"

std::vector<std::vector<VisibleGameObject *>> * ObjectFactory::genStaticObjects()
{
	for (int y = 0; y < Map::mapHeight(); y++)
		for (int x = 0; x < Map::mapHeight(); x++)
		{
			switch (Map::at(x, y))
			{
				case grass:
					break;
				case unbreakableBlocks:
					break;
				case breakableBlocks:
					break;
				case player:
					break;
				case goomba:
					break;
				case koopaTroopa:
					break;
				case powerBlock:
					break;
				case healthBlock:
					break;
				default:
					break;
			}
		}
}

std::list<*VisibleGameObjects> * ObjectFactory::genDynamicObjects()
{
	std::list * staticObjects = new std::list;
	for (int y = 0; y < Map::mapHeight(); y++)
		for (int x = 0; x < Map::mapHeight(); x++)
		{
			switch (Map::at(x, y))
			{
				case player:
					break;
				case goomba:
					break;
				case koopaTroopa:
					break;
				default:
					break;
			}
		}

	return staticObjects;
}
