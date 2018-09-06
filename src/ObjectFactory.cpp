//
// Created by Patrick RUSSELL on 2018/09/03.
//

#include <Grass.hpp>
#include <Block.hpp>
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
	delete _grass;
}

ObjectFactory::ObjectFactory()
{
}

void ObjectFactory::initModelTextures()
{
	_player = new ModelTexture("../assets/objects/mario_walking_1.obj");
	_unbreakableBlock = new ModelTexture("../assets/objects/iron_block.obj");
	_breakableBlock = new ModelTexture("../assets/objects/brick_block.obj");
	_goomba = new ModelTexture("../assets/objects/goomba.obj");
	_koopaTroopa = new ModelTexture("../assets/objects/koopa_troopa.obj");
	_powerBlock = new ModelTexture("../assets/objects/brick_block.obj");
	_healthBlock = new ModelTexture("../assets/objects/brick_block.obj");
	_grass = new ModelTexture("../assets/objects/grass_block_light.obj");
}

std::vector<std::vector<VisibleGameObject *>> ObjectFactory::genStaticObjects()
{
	std::vector<std::vector<VisibleGameObject * >> result;

	for (int y = 0; y < Map::mapHeight(); y++)
	{
		std::vector<VisibleGameObject * > innerResult;

		for (int x = 0; x < Map::mapWidth(); x++)
		{
			switch (Map::at(x, y))
			{
				case grass:
					innerResult.push_back(new Grass(*_grass, x, y, false));
					break;
				case unbreakableBlocks:
					innerResult.push_back(new Block(*_unbreakableBlock, x, y, false));
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
