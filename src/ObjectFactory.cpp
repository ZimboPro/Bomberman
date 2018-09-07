//
// Created by Patrick RUSSELL on 2018/09/03.
//

#include <Grass.hpp>
#include <Block.hpp>
#include "ObjectFactory.hpp"
#include "Map.hpp"
#include "Game.hpp"

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
/*	_player = new Model_Texture("../assets/pickups/heart.obj");
	_unbreakableBlock = new Model_Texture("../assets/objects/iron_block.obj");
	_breakableBlock = new Model_Texture("../assets/objects/brick_block.obj");
	_goomba = new Model_Texture("../assets/objects/goomba.obj");
	_koopaTroopa = new Model_Texture("../assets/objects/koopa_troopa.obj");
	_powerBlock = new Model_Texture("../assets/objects/brick_block.obj");
	_healthBlock = new Model_Texture("../assets/objects/brick_block.obj");
	_grass = new Model_Texture("../assets/objects/grass_block_light.obj");
  */
	_player = new Model_Texture("../assets/pickups/heart.obj");
    _unbreakableBlock = new Model_Texture("../assets/pickups/power_up.obj");
    _breakableBlock = new Model_Texture("../assets/pickups/heart.obj");
    _goomba = new Model_Texture("../assets/pickups/heart.obj");
    _koopaTroopa = new Model_Texture("../assets/pickups/heart.obj");
    _powerBlock = new Model_Texture("../assets/pickups/heart.obj");
    _healthBlock = new Model_Texture("../assets/pickups/heart.obj");
    _grass = new Model_Texture("../assets/pickups/heart.obj");
}

std::vector<std::vector<VisibleGameObject *>> ObjectFactory::genStaticObjects()
{
	std::vector<std::vector<VisibleGameObject * >> result;

	for (size_t y = 0; y < Map::height(); y++)
	{
		std::vector<VisibleGameObject * > innerResult;
		std::cout << "Row " << y << std::endl;

		for (size_t x = 0; x < Map::width(); x++)
		{
			std::cout << Map::at(x, y);
			switch (Map::at(x, y))
			{
				case grass:
					innerResult.push_back(new Grass(*_grass, x, y));
					break;
				case unbreakableBlocks:
					innerResult.push_back(new Block(*_unbreakableBlock, x, y, false));
					break;
				case breakableBlocks:
					innerResult.push_back(new Block(*_breakableBlock, x, y, true));
					break;
				default:
					std::cout << "Default " << std::endl;
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

	for (int y = 0; y < Map::height(); y++)
		for (int x = 0; x < Map::width(); x++)
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
