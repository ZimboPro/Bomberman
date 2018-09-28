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
#include <game_elements/Pipe.hpp>

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::ObjectFactory(ObjectFactory const & src)
{
	*this = src;
}

ObjectFactory::~ObjectFactory()
{
	for (size_t i = 0; i < this->_player.size(); i++)
		delete _player[i];
	for (size_t i = 0; i < this->_goomba.size(); i++)
		delete _goomba[i];
	// delete _goomba;
	// for (size_t i = 0; i < this->_koopaTroopa.size(); i++)
		// delete _koopaTroopa[i];
	for (size_t i = 0; i < this->_koopaTroopa.size(); i++)
		delete _koopaTroopa[i];
	delete _unbreakableBlock;
	delete _breakableBlock;
	delete _powerBlock;
	delete _healthBlock;
	delete _grass;
	delete _fire;
}

void ObjectFactory::initModelTextures()
{
	//todo display loading screen
	Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	_player.emplace_back(new Model_Texture("../../Assets/game_models/mario_walking_2.obj"));
	_player.emplace_back(new Model_Texture("../../Assets/game_models/mario_walking_1.obj"));
	_player.emplace_back(new Model_Texture("../../Assets/game_models/mario_walking_3.obj"));
	
	Game::_loadingScreen.display();
	_goomba.emplace_back(new Model_Texture("../../Assets/game_models/goomba_2.obj"));
	_goomba.emplace_back(new Model_Texture("../../Assets/game_models/goomba_1.obj"));
	Game::_loadingScreen.display();	
	_goomba.emplace_back(new Model_Texture("../../Assets/game_models/goomba_3.obj"));
	_goomba.emplace_back(new Model_Texture("../../Assets/game_models/goomba_burnt.obj"));
	
	Game::_loadingScreen.display();
	_koopaTroopa.emplace_back(new Model_Texture("../../Assets/game_models/koopa_troopa_2.obj"));
	_koopaTroopa.emplace_back(new Model_Texture("../../Assets/game_models/koopa_troopa_1.obj"));
	Game::_loadingScreen.display();	
	_koopaTroopa.emplace_back(new Model_Texture("../../Assets/game_models/koopa_troopa_3.obj"));
	_koopaTroopa.emplace_back(new Model_Texture("../../Assets/game_models/koopa_troopa_burnt.obj"));
	
	Game::_loadingScreen.display();
	_unbreakableBlock = new Model_Texture("../../Assets/game_models/iron_block.obj");
	_breakableBlock = new Model_Texture("../../Assets/game_models/brick_block.obj");
	Game::_loadingScreen.display();	
	_powerBlock = new Model_Texture("../../Assets/game_models/power_up.obj");
	_healthBlock = new Model_Texture("../../Assets/game_models/heart.obj");
	
	Game::_loadingScreen.display();
	_grass = new Model_Texture("../../Assets/game_models/grass_block_light.obj");
	_bomb = new Model_Texture("../../Assets/game_models/bomb_carry.obj");
	Game::_loadingScreen.display();	
	_fire = new Model_Texture("../../Assets/game_models/fire.obj");
	_pipe = new Model_Texture("../../Assets/game_models/pipe.obj");
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

std::vector<std::vector<std::shared_ptr<VisibleGameObject>>> ObjectFactory::genStaticObjects()
{
	std::vector<std::vector<std::shared_ptr<VisibleGameObject>>> result;

	for (size_t y = 0; y < Map::height(); y++)
	{
		std::vector<std::shared_ptr<VisibleGameObject>> innerResult;
		for (size_t x = 0; x < Map::width(); x++)
		{
			switch (Map::at(x, y))
			{
				case breakableBlocks:
					innerResult.push_back(std::shared_ptr<VisibleGameObject> (new Block(*_breakableBlock, x, y, true)));
					break;
				case unbreakableBlocks:
					innerResult.push_back(std::shared_ptr<VisibleGameObject> (new Block(*_unbreakableBlock, x, y, false)));
					break;
				case powerBlock:
					innerResult.push_back(std::shared_ptr<VisibleGameObject> (new Block(*_breakableBlock, x, y, true)));
					break;
				case healthBlock:
					innerResult.push_back(std::shared_ptr<VisibleGameObject> (new Block(*_breakableBlock, x, y, true)));
					break;
				case gate:
					innerResult.push_back(std::shared_ptr<VisibleGameObject> (new Block(*_breakableBlock, x, y, true)));
					break;
				default:
					innerResult.push_back(std::shared_ptr<VisibleGameObject> (new VisibleGameObject));
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
					result->push_back(std::shared_ptr<VisibleGameObject> (new Player(_player, x, y)));
					Map::setPlayerStart(x, y);
					break;
				case goomba:
					GameInterface::incrementTotalEnemies();
					result->push_back(std::shared_ptr<VisibleGameObject> (new Goomba(_goomba, x, y)));
					break;
				case koopaTroopa:
					GameInterface::incrementTotalEnemies();
					result->push_back(std::shared_ptr<VisibleGameObject> (new KoopaTroopa(_koopaTroopa, x, y)));
					break;
				case powerBlock:
					result->push_back(std::shared_ptr<VisibleGameObject> (new PowerBlock(*_powerBlock, x, y)));
					break;
				case healthBlock:
					result->push_back(std::shared_ptr<VisibleGameObject> (new HealthBlock(*_healthBlock, x, y)));
					break;
				case gate:
					result->push_back(std::shared_ptr<VisibleGameObject> (new Pipe(*_pipe, x, y)));
				default:
					break;
			}
		}
	return result;
}
