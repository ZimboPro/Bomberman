//
// Created by Patrick RUSSELL on 2018/09/03.
//

#include <game_elements/Grass.hpp>
#include <game_elements/Block.hpp>
#include <game_elements/Player.hpp>
#include <game_elements/Goomba.hpp>
#include <game_elements/KoopaTroopa.hpp>
#include <game_elements/powerBlock.hpp>
#include "game_elements/HealthBlock.hpp"
#include "ObjectFactory.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "game_elements/Bomb.hpp"
#include <string>

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
	//todo display loading screen
	_player = new Model_Texture("../../Assets/game_models/mario_walking_1.obj");
	_unbreakableBlock = new Model_Texture("../../Assets/game_models/iron_block.obj");
	_breakableBlock = new Model_Texture("../../Assets/game_models/brick_block.obj");
	_goomba = new Model_Texture("../../Assets/game_models/goomba.obj");
	_koopaTroopa = new Model_Texture("../../Assets/game_models/koopa_troopa.obj");
	_powerBlock = new Model_Texture("../../Assets/game_models/power_up.obj");
	_healthBlock = new Model_Texture("../../Assets/game_models/heart.obj");
	_grass = new Model_Texture("../../Assets/game_models/grass_block_light.obj");
	_bomb = new Model_Texture("../../Assets/game_models/bomb_carry.obj");
}

VisibleGameObject * ObjectFactory::newBomb(float x, float y)
{
	return new Bomb(*_bomb, x, y);
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
					break;
				case unbreakableBlocks:
					innerResult.push_back(new Block(*_unbreakableBlock, x, y, false));
					break;
				default:
					innerResult.push_back(new VisibleGameObject);
					break;
			}
		}
		result.push_back(innerResult);
	}
	return result;
}

std::list<std::shared_ptr<VisibleGameObject>> * ObjectFactory::genGrass()
{
	auto result = new std::list<std::shared_ptr<VisibleGameObject>>;
//	std::shared_ptr<std::list<std::shared_ptr<VisibleGameObject>>> result;

	for (size_t y = 0; y < Map::height(); y++)
		for (size_t x = 0; x < Map::width(); x++)
		{
			VisibleGameObject * grass = new Grass(*_grass, x, y);
			std::shared_ptr<VisibleGameObject> grassPtr(grass);
//			result->push_back(new Grass(*_grass, x, y));
			result->push_back(grassPtr);
//			result->push_back()
		}
	return result;
}

std::list<VisibleGameObject *> * ObjectFactory::genDynamicAndPickUpObjects()
{
	auto result = new std::list<VisibleGameObject *>;

	for (size_t y = 0; y < Map::height(); y++)
		for (size_t x = 0; x < Map::width(); x++)
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
					result->push_back(new PowerBlock(*_powerBlock, x, y));
					break;
				case healthBlock:
					result->push_back(new HealthBlock(*_healthBlock, x, y));
					break;
				default:
					break;
			}
		}
	return result;
}
