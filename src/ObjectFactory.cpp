//
// Created by Patrick RUSSELL on 2018/09/03.
//

#include <Grass.hpp>
#include <Block.hpp>
#include <Player.hpp>
#include <Goomba.hpp>
#include <KoopaTroopa.hpp>
#include <PowerBlock.hpp>
#include "HealthBlock.hpp"
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
	_player = new Model_Texture("../assets/objects/mario_walking_1.obj");
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

	for (size_t y = 0; y < Map::height(); y++)
	{
		std::vector<VisibleGameObject * > innerResult;

		for (size_t x = 0; x < Map::width(); x++)
		{
			switch (Map::at(x, y))
			{
				case breakableBlocks:
					innerResult.push_back(new Block(*_breakableBlock, x, y, true));
					innerResult.push_back(new Grass(*_grass, x, y));
					break;
				default:
					innerResult.push_back(new Grass(*_grass, x, y));
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
				case unbreakableBlocks:
					result->push_back(new Block(*_unbreakableBlock, x, y, false));
					break;
				case player:
					result->push_back(new Player(*_player, x, y));
					break;
				case goomba:
					result->push_back(new Goomba(*_goomba, x, y));
					break;
				case koopaTroopa:
					result->push_back(new KoopaTroopa(*_koopaTroopa, x, y));
					break;
				case powerBlock:
					result->push_back(new PowerBlock(*_koopaTroopa, x, y));
					break;
				case healthBlock:
					result->push_back(new HealthBlock(*_koopaTroopa, x, y));
					break;
				default:
					break;
			}
		}
	return result;
}
