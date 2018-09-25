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

GameObjectManager::GameObjectManager() = default;

GameObjectManager::GameObjectManager(GameObjectManager const & src) 
{
	*this = src;
}

GameObjectManager::~GameObjectManager()
= default;

void GameObjectManager::init()
{
	Map::readInRandomMap(0);
	_factory.initModelTextures();
	_staticObjects = _factory.genStaticObjects();
	_dynamicObjects = _factory.genDynamicAndPickUpObjects();
	_grass = _factory.genGrass();
	_initialized = true;
}

void GameObjectManager::drawAll(Shaders & shader)
{
	if (!_initialized) throw Error::AssetError("Models not initialized");
	
	for (auto &_staticObject : _staticObjects)
		for (auto &x : _staticObject)
		{
			if(x->isLoaded())
				x->Draw(shader);
		}

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
	if (Map::getLevelHolder().size() > Map::getLevel())
	{
		Map::readInRandomMap(seed);
		Map::levelDown();
	}
	clearObjects();
}

void GameObjectManager::clearObjects()
{
	_staticObjects.clear();
	_dynamicObjects->clear();
	_grass->clear();
	delete _dynamicObjects;
	delete _grass;
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
	int Down = 0;
	int Up = 1;

	if (seed == 0)
	{
		changeLevel(0);
		initLevel();
	}
	else if (seed < 3)
	{
		changeLevel(Map::getLevel() + 1);		
		initLevel();
	}
	else
		std::cout << "Display Game Over" << std::endl;
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
	std::shared_ptr<VisibleGameObject> obj(_factory.newVGO(type, x, y));
	_dynamicObjects->push_back(obj);
}

bool GameObjectManager::setFireAndContinue(float x, float y)
{
	if (_staticObjects[y][x]->isLoaded())
	{
		if (_staticObjects[y][x]->isBreakable())
		{
			_staticObjects[y][x]->kill();
			addDynamicObject(fire, x, y);
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

objectTypes GameObjectManager::collidesWith(BoundingBox & box, objectTypes type)
{
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
				_dynamicObjects->erase(iter);
			return collType;
		}
	}
	return grass;
}

std::vector<std::vector<std::shared_ptr<VisibleGameObject>>> GameObjectManager::_staticObjects;
std::list<std::shared_ptr<VisibleGameObject> > * GameObjectManager::_dynamicObjects;
std::list<std::shared_ptr<VisibleGameObject>> * GameObjectManager::_grass;
ObjectFactory GameObjectManager::_factory;
bool GameObjectManager::_initialized = false;
