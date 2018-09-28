//
// Created by Patrick RUSSELL on 2018/08/24.
//

#include <iostream>
#include "GameObjectManager.hpp"
#include "ObjectFactory.hpp"
#include <glm/vec4.hpp>
#include <Map.hpp>
#include <memory>
#include <game_elements/Bomb.hpp>
#include <Error.hpp>
#include <GameInterface.hpp>
#include "Screens/GameWon.hpp"
#include "Game.hpp"

GameObjectManager::GameObjectManager() = default;

GameObjectManager::GameObjectManager(GameObjectManager const & src) 
{
	*this = src;
}

GameObjectManager::~GameObjectManager()
= default;

void GameObjectManager::init()
{
	_factory.initModelTextures();
}

void GameObjectManager::drawAll(Shaders & shader)
{
	if (!_initialized) throw Error::AssetError("Models not initialized");
	
	for (auto &_staticObject : _staticObjects)
	{
		for (auto &x : _staticObject)
		{
			if(x->isLoaded())
				x->Draw(shader);
		}
	}
	// std::cout << "-";

	// for(size_t row = 0; row < _staticObjects.size(); row++)
	// {
	// 	for(size_t col = 0; col < _staticObjects[row].size(); col++)
	// 	{
	// 		if (_staticObjects[row][col]->isLoaded())
	// 			_staticObjects[row][col]->Draw(shader);
	// 	}
	// }
	// std::cout << "1st\n";
	for (auto &_grass : *_grass)
	{
		_grass->Draw(shader);
	}

	for (auto &_dynamicObject : *_dynamicObjects)
	{
		if (_dynamicObject->isLoaded())
			_dynamicObject->Draw(shader);
	}

}

void GameObjectManager::updateAll(float elapsedTime)
{
	if (!_initialized) throw Error::AssetError("Models not initialized");

	for (auto &_staticObject : _staticObjects)
		for (auto &x : _staticObject)
		{
			if(x->isLoaded() && x->isBreakable())
				x->Update(elapsedTime);
		}

	for (auto &_dynamicObject : *_dynamicObjects)
	{
		if(_dynamicObject->isLoaded())
			_dynamicObject->Update(elapsedTime);
	}
}

void GameObjectManager::changeLevel(int seed)
{
	_initialized = false;
	clearObjects();
	if (Map::size() != 0)
		killItWithFire();
	Map::readInRandomMap(seed);
	initLevel();
}

void GameObjectManager::loadLevel(std::vector<std::vector<char>> map)
{
	Map::setMap(map);
	initLevel();
}

void GameObjectManager::clearObjects()
{
	if (_staticObjects.size() > 0)
	{
		// _staticObjects.clear();
		for (size_t i = 0; i < _staticObjects.size(); i++)
		{
			_staticObjects[i].clear();
		}
		_staticObjects.clear();
		_dynamicObjects->clear();
		delete _dynamicObjects;
		_grass->clear();
		delete _grass;
	}
}

void GameObjectManager::initLevel()
{
	_staticObjects = _factory.genStaticObjects();
	_dynamicObjects = _factory.genDynamicAndPickUpObjects();
	_grass = _factory.genGrass();
	_initialized = true;
}

void GameObjectManager::newLevel(int seed)
{
	if (seed == 0)
		changeLevel(0);
	else if (seed <= 3)
		changeLevel(seed);		
	else
	{
		GameWon gamewon;
		gamewon.show();
		Game::setGameStateGameWon();
	}
}

bool GameObjectManager::intersects(BoundingBox obj1, BoundingBox obj2)
{
	if (obj2.x1 >= obj1.x1 && obj2.x1 <= obj1.x2 && obj2.y1 >= obj1.y1 && obj2.y1 <= obj1.y2)
		return true;

	if (obj2.x2 >= obj1.x1 && obj2.x2 <= obj1.x2 && obj2.y1 >= obj1.y1 && obj2.y1 <= obj1.y2)
		return true;
	
	if (obj1.x1 >= obj2.x1 && obj1.x1 <= obj2.x2 && obj1.y1 >= obj2.y1 && obj1.y1 <= obj2.y2)
		return true;

	if (obj1.x2 >= obj2.x1 && obj1.x2 <= obj2.x2 && obj1.y1 >= obj2.y1 && obj1.y1 <= obj2.y2)
		return true;

	return false;
}

void GameObjectManager::addDynamicObject(objectTypes type, float x, float y)
{
	if (type != bomb || !_staticObjects[y][x]->isLoaded())
	{
		std::shared_ptr<VisibleGameObject> obj(_factory.newVGO(type, x, y));
		BoundingBox box = obj.get()->getBoundingBox();
		if (type == bomb && collidesWith(box, type) == grass)
			_dynamicObjects->push_back(obj);
		else if (type != bomb)
			_dynamicObjects->push_back(obj);
	}
}

bool GameObjectManager::setFireAndContinue(float x, float y)
{
	if (_staticObjects[y][x]->isLoaded())
	{
		if (_staticObjects[y][x]->isBreakable())
		{
			_staticObjects[y][x]->kill();
			addDynamicObject(fire, x, y);
			Map::removeAtPosition(x, y);
			return true;
		}
		else
			return false;
	}
	addDynamicObject(fire, x, y);
	return true;
}


void GameObjectManager::spawnFire(VisibleGameObject *bomb)
{
	float burnRange = 2 * GameInterface::getRangeMultiplier();

	float bombX = bomb->getPosition().x;
	float bombY = bomb->getPosition().z;

	float startX = ((bombX - burnRange >= 0) ? bombX - burnRange : 0);
	float startY = ((bombY - burnRange >= 0) ? bombY - burnRange : 0);
	float endX = ((bombX + burnRange < static_cast<float>(_staticObjects[0].size())) ? bombX + burnRange : static_cast<float>(_staticObjects[0].size()));
	float endY = ((bombY + burnRange < static_cast<float>(_staticObjects.size())) ? bombY + burnRange : static_cast<float>(_staticObjects.size()));

	for(float y = bombY; y >= startY; y--)
		if (!setFireAndContinue(bombX, y))
			break;
	for(float y = bombY; y <= endY; y++)
		if (!setFireAndContinue(bombX, y))
			break;
	for(float x = bombX - 1; x >= startX; x--)
		if (!setFireAndContinue(x, bombY))
			break;
	for(float x = bombX + 1; x <= endX; x++)
		if (!setFireAndContinue(x, bombY))
			break;
}

void GameObjectManager::explodeBomb(VisibleGameObject *bomb)
{
	spawnFire(bomb);
	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
	{
		if (bomb == (*iter).get())
		{
			_dynamicObjects->erase((iter));
			return ;
		}
	}
}

void GameObjectManager::removeDynamicObject(VisibleGameObject *obj)
{
	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
	{
		if (obj == (*iter).get())
		{
			_dynamicObjects->erase(iter);
			return ;
		}
	}
}

void GameObjectManager::killPlayer()
{
	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
	{
		if ((*iter).get()->getType() == player)
		{
			(*iter).get()->kill();
			return ;
		}
	}
}

bool GameObjectManager::validBox(BoundingBox & box)
{
	float maxX = static_cast<float>(_staticObjects[0].size());
	float maxY = static_cast<float>(_staticObjects.size());
	if (box.x1 >= maxX || box.x2 >= maxX || box.y1 >= maxY || box.y2 >= maxY)
		return false;
	else if (box.x1 < 0 || box.x2 < 0 || box.y1 < 0 || box.y2 < 0)
		return false;

	return true;
}

objectTypes GameObjectManager::collidesWith(BoundingBox & box, objectTypes type)
{
	if (!validBox(box))
		return fire;

	if (_staticObjects[box.y1][box.x1]->isLoaded())
	{
		if (_staticObjects[box.y1][box.x1]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}
	else if (_staticObjects[box.y1][box.x2]->isLoaded())
	{
		if (_staticObjects[box.y2][box.x2]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}
	else if (_staticObjects[box.y2][box.x1]->isLoaded())
	{
		if (_staticObjects[box.y2][box.x1]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}
	else if (_staticObjects[box.y2][box.x2]->isLoaded())
	{
		if (_staticObjects[box.y2][box.x2]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}

	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
	{
		if ((*iter)->getType() != type && (*iter)->isLoaded() && intersects(box, (*iter)->getBoundingBox()))
		{
			objectTypes collType = (*iter)->getType();
			if((collType == healthBlock || collType == powerBlock) && type == player)
			{
				if (collType == healthBlock )
				{
					if (Game::_settings.sound)
						ServiceLocator::getAudio()->playSound("../../Assets/sounds/gameplay/pickup_health.wav");
					GameInterface::adjustLives(1);
				}
				else
				{
					if (Game::_settings.sound)
						ServiceLocator::getAudio()->playSound("../../Assets/sounds/gameplay/get_power_up.wav");
					GameInterface::increaseRangeMultiplier();
					GameInterface::adjustScore(20);
				}
				_dynamicObjects->erase(iter);
			}
			return collType;
		}
	}
	return grass;
}

void GameObjectManager::killItWithFire()
{
	clearObjects();
	Map::destroyEverything();
}

void GameObjectManager::collidesWithPlayer()
{
	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
	{
		if ((*iter).get()->getType() == player)
		{
			Rectangle box = (*iter).get()->getBoundBox();
			for (auto fireIter = _dynamicObjects->begin(); fireIter != _dynamicObjects->end(); fireIter++)
			{
				if ((*fireIter).get()->getType() == fire)
				{
					if ((*fireIter).get()->Collision(box))
					{
						(*iter).get()->kill();
						return;
					}
				}
			}
			break;
		}
	}
}

std::vector<std::vector<std::shared_ptr<VisibleGameObject>>> GameObjectManager::_staticObjects;
std::list<std::shared_ptr<VisibleGameObject> > * GameObjectManager::_dynamicObjects;
std::list<std::shared_ptr<VisibleGameObject>> * GameObjectManager::_grass;
ObjectFactory GameObjectManager::_factory;
bool GameObjectManager::_initialized = false;
