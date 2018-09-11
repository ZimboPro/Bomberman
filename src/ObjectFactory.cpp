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
#include "Game.hpp"
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
	// _player = new Model_Texture("../assets/objects/mario_walking_1.obj");
	_unbreakableBlock = new Model_Texture("../assets/objects/Enviroment/iron_block.obj");
	_breakableBlock = new Model_Texture("../assets/objects/Enviroment/brick_block.obj");
	_goomba = new Model_Texture("../assets/objects/goomba/goomba.obj");
	_koopaTroopa = new Model_Texture("../assets/objects/Koopa/koopa_troopa.obj");
	_powerBlock = new Model_Texture("../assets/objects/Enviroment/brick_block.obj");
	_healthBlock = new Model_Texture("../assets/objects/Enviroment/brick_block.obj");
	_grass = new Model_Texture("../assets/objects/Enviroment/grass_block_light.obj");
//	_grass = new Model_Texture("../assets/objects/grass/grass_block_light.obj");
//	_grass = new Model_Texture("../assets/new_grass/untitled.obj");
}

std::vector<std::vector<VisibleGameObject *>> ObjectFactory::genStaticObjects()
{
	std::vector<std::vector<VisibleGameObject * >> result;
	std::cout << "Printing Map" << std::endl;
	Map::printMap();

	for (size_t y = 0; y < Map::height(); y++)
	{
		std::vector<VisibleGameObject * > innerResult;

		for (size_t x = 0; x < Map::width(); x++)
		{
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
				case player:
					innerResult.push_back(new Grass(*_grass, x, y));
					break;
				case goomba:
					innerResult.push_back(new Grass(*_grass, x, y));
					break;
				case koopaTroopa:
					innerResult.push_back(new Grass(*_grass, x, y));
					break;
				case powerBlock:
					innerResult.push_back(new Block(*_breakableBlock, x, y, true));
					break;
				case healthBlock:
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
