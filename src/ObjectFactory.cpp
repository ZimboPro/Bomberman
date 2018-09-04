//
// Created by Patrick RUSSELL on 2018/09/03.
//

#include "ObjectFactory.hpp"
#include "Map.hpp"

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
	_player = new Model("../assets/objects/mario_walking_1.png");
	_unbreakableBlock = new Model("assets/objects/iron_block.png");
	_breakableBlock = new Model("assets/objects/brick_block.png");
	_goomba = new Model("assets/objects/goomba.obj");
	_koopaTroopa = new Model("assets/objects/koopa_troopa.obj");
	_powerBlock = new Model("assets/objects/brick_block.png");
	_healthBlock = new Model("assets/objects/brick_block.png");


}

std::vector<std::vector<VisibleGameObject *>> * ObjectFactory::genStaticObjects()
{
	auto result = new std::vector<std::vector<VisibleGameObject * >>;

	for (int y = 0; y < Map::mapHeight(); y++)
	{
		auto innerResult = new std::vector<VisibleGameObject * >;

		for (int x = 0; x < Map::mapWidth(); x++)
		{
			switch (Map::at(x, y))
			{
				case grass:
					innerResult.push_back(new Grass(*_grass, x, y));
					break;
				case unbreakableBlocks:
					innerResult.push_back(new Block(*_unBreakableBlock, x, y, false));
					break;
				case breakableBlocks:
					innerResult.push_back(new Block(*_breakableBlock, x, y, true));
					break;
				default:
					break;
			}
		}
		result.push_back(innerResult);
	}
	return result;
}


std::list<VisibleGameObject *> * ObjectFactory::genDynamicAndPickUpObjects()
{
	auto result = new std::list<VisibleGameObject *>;

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

	return result;
}
