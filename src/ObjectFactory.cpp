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
	_player = new Model_Texture("../assets/pickups/heart.obj");
	_unbreakableBlock = new Model_Texture("../assets/objects/iron_block.obj");
	_breakableBlock = new Model_Texture("../assets/objects/brick_block.obj");
	_goomba = new Model_Texture("../assets/objects/goomba.obj");
	_koopaTroopa = new Model_Texture("../assets/objects/koopa_troopa.obj");
	_powerBlock = new Model_Texture("../assets/objects/brick_block.obj");
	_healthBlock = new Model_Texture("../assets/objects/brick_block.obj");
	_grass = new Model_Texture("../assets/objects/grass_block_light.obj");
}

std::vector<std::vector<VisibleGameObject *>> ObjectFactory::genStaticObjects()
{
	std::vector<std::vector<VisibleGameObject * >> result;

	float scaleFactor = 2;
	for (size_t y = 0; y < Map::height(); y++)
	{
		std::vector<VisibleGameObject * > innerResult;

		for (size_t x = 0; x < Map::width(); x++)
		{
			switch (Map::at(x, y))
			{
				case grass:
					innerResult.push_back(new Grass(*_grass, x * scaleFactor, y * scaleFactor));
					break;
				case unbreakableBlocks:
					innerResult.push_back(new Block(*_unbreakableBlock, x * scaleFactor, y * scaleFactor, false));
					break;
				case breakableBlocks:
					innerResult.push_back(new Block(*_breakableBlock, x * scaleFactor, y * scaleFactor, true));
					break;
				case player:
					innerResult.push_back(new Grass(*_grass, x * scaleFactor, y * scaleFactor));
					break;
				case goomba:
					innerResult.push_back(new Grass(*_grass, x * scaleFactor, y * scaleFactor));
					break;
				case koopaTroopa:
					innerResult.push_back(new Grass(*_grass, x * scaleFactor, y * scaleFactor));
					break;
				case powerBlock:
					innerResult.push_back(new Block(*_breakableBlock, x * scaleFactor, y * scaleFactor, true));
					break;
				case healthBlock:
					innerResult.push_back(new Block(*_breakableBlock, x * scaleFactor, y * scaleFactor, true));
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
