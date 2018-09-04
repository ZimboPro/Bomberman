//
// Created by Patrick RUSSELL on 2018/09/03.
//

#include "ObjectFactory.hpp"
#include "Map"

ObjectFactory::~ObjectFactory()
{
	delete _player;
	delete _unbreakableBlock;
	delete _breakableBlock;
	delete _goomba;
	delete _koopaTroopa;
	delete _powerBlock;
	delete _healthBlock;
}

ObjectFactory::ObjectFactory()
{
	_player = new Model("../assets/objects/mario_walking_1.obj");
	_unbreakableBlock = new Model("../assets/objects/iron_block.obj");
	_breakableBlock = new Model("../assets/objects/brick_block.obj");
	_goomba = new Model("../assets/objects/goomba.obj");
	_koopaTroopa = new Model("../assets/objects/koopa_troopa.obj");
	_powerBlock = new Model("../assets/objects/power_up.obj");
	_healthBlock = new Model("../assets/objects/heart.obj");
}

std::vector<std::vector<VisibleGameObject *>> * ObjectFactory::genStaticObjects()
{
	auto result = new std::vector<std::vector<VisibleGameObject * >>;

	for (int y = 0; y < Map::mapHeight(); y++)
		for (int x = 0; x < Map::mapWidth(); x++)
		{
			switch (Map::at(x, y))
			{
				case grass:
					break;
				case unbreakableBlocks:
					break;
				case breakableBlocks:
					break;
				default:
					break;
			}
		}

	return result;
}


std::list<*VisibleGameObjects> * ObjectFactory::genDynamicAndPickUpObjects()
{
	auto result  = new std::list<VisibleGameObject *>;

	for (int y = 0; y < Map::mapHeight(); y++)
		for (int x = 0; x < Map::mapWidth(); x++)
		{
			switch (Map::at(x, y))
			{
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

	return staticObjects;
}
