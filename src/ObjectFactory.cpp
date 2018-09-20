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
#include "Game.hpp"
#include "game_elements/Bomb.hpp"
#include <string>
#include <game_elements/Fire.hpp>

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::ObjectFactory(ObjectFactory const & src)
{
	*this = src;
}

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
	delete _fire;
}

void ObjectFactory::initModelTextures()
{
	//todo display loading screen
	_player = new Model_Texture("../../Assets/game_models/mario_walking_1.obj");
	_unbreakableBlock = new Model_Texture("../../Assets/game_models/iron_block.obj");
	_breakableBlock = new Model_Texture("../../Assets/game_models/brick_block.obj");
	_goomba = new Model_Texture("../../Assets/game_models/goomba_1.obj");
	_koopaTroopa = new Model_Texture("../../Assets/game_models/koopa_troopa_1.obj");
	_powerBlock = new Model_Texture("../../Assets/game_models/power_up.obj");
	_healthBlock = new Model_Texture("../../Assets/game_models/heart.obj");
	_grass = new Model_Texture("../../Assets/game_models/grass_block_light.obj");
	_bomb = new Model_Texture("../../Assets/game_models/bomb_carry.obj");
	_fire = new Model_Texture("../../Assets/game_models/fire.obj");
}

VisibleGameObject * ObjectFactory::newBomb(float x, float y)
{
	return new Bomb(*_bomb, x, y);
}

VisibleGameObject * ObjectFactory::newVGO(objectTypes type, float x, float y)
{
	switch (type)
	{
		case fire:
			return new Fire(*_fire, x, y);
		case bomb:
			return new Bomb(*_bomb, x, y);
		default:
			return NULL;
	}
}

std::vector<std::vector<VisibleGameObject *>> ObjectFactory::genStaticObjects()
{
	std::vector<std::vector<VisibleGameObject * >> result;
	// std::cout << "Printing Map" << std::endl;
	// Map::printMap();

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

	for (size_t y = 0; y < Map::height(); y++)
		for (size_t x = 0; x < Map::width(); x++)
		{
			std::shared_ptr<VisibleGameObject> grassPtr(new Grass(*_grass, x, y));
			result->push_back(grassPtr);
		}
	return result;
}

std::list<std::shared_ptr<VisibleGameObject>> * ObjectFactory::genDynamicAndPickUpObjects()
{
	auto result = new std::list<std::shared_ptr<VisibleGameObject>>;

	for (size_t y = 0; y < Map::height(); y++)
		for (size_t x = 0; x < Map::width(); x++)
		{
			switch (Map::at(x, y))
			{
				case player:
					result->push_back(std::shared_ptr<VisibleGameObject> (new Player(*_player, x, y)));
					break;
				case goomba:
					result->push_back(std::shared_ptr<VisibleGameObject> (new Goomba(*_goomba, x, y)));
					break;
				case koopaTroopa:
					result->push_back(std::shared_ptr<VisibleGameObject> (new KoopaTroopa(*_koopaTroopa, x, y)));
					break;
				case powerBlock:
					result->push_back(std::shared_ptr<VisibleGameObject> (new PowerBlock(*_powerBlock, x, y)));
					break;
				case healthBlock:
					result->push_back(std::shared_ptr<VisibleGameObject> (new HealthBlock(*_healthBlock, x, y)));
					break;
				default:
					break;
			}
		}
	return result;
}
