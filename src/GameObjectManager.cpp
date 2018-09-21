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

GameObjectManager::GameObjectManager() {}

GameObjectManager::GameObjectManager(GameObjectManager const & src) 
{
	*this = src;
}

GameObjectManager::~GameObjectManager()
{
}

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
	if (!_initialized)
		throw Error::AssetError("Models not initialized");
	for(size_t y = 0; y < _staticObjects.size(); y++)
		for (size_t x = 0; x < _staticObjects[y].size(); x++)
		{
			_staticObjects[y][x]->Draw(shader);
		}

	for (auto iter = _grass->begin(); iter != _grass->end(); iter++)
	{
		(*iter)->Draw(shader);
	}

	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
	{
		(*iter)->Draw(shader);
	}
}

void GameObjectManager::updateAll(float elapsedTime)
{
	if (!_initialized)
		throw Error::AssetError("Models not initialized");
	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
	{
		(*iter)->Update(elapsedTime);
	}
}

void GameObjectManager::clearLevel()
{
	_staticObjects.clear();
	_dynamicObjects->clear();
}

void GameObjectManager::initLevel()
{
	
}

void GameObjectManager::newLevel()
{
	clearLevel(); // empty the data structures: _DynamicObjetcs, _Grass and _static Objetcs
	initLevel(); // makes call to factory to init the datastructures with fresh objects
}

bool GameObjectManager::intersects(BoundingBox obj1, BoundingBox obj2)
{
	float x1 = obj1.x1;
	float maxX1 = obj1.x2;
	float y1 = obj1.y1;
	float maxY1 = obj1.y2;

	float x2 = obj2.x1;
	float maxX2 = obj2.x2;
	float y2 = obj2.y1;
	float maxY2 = obj2.y2;

	std::cout << x2 << std::endl;
	if (x2 >= x1 && x2 <= maxX1 && y2 >= y1 && y2 <= maxY1)
		return true;

	if (maxX2 >= x1 && maxX2 <= maxX1 && y2 >= y1 && y2 <= maxY1)
		return true;
	
	if (x1 >= x2 && x1 <= maxX2 && y1 >= y2 && y1 <= maxY2)
		return true;

	if (maxX1 >= x2 && maxX1 <= maxX2 && y1 >= y2 && y1 <= maxY2)
		return true;

	return false;
}

void GameObjectManager::addDynamicObject(objectTypes type, float x, float y)
{
	std::shared_ptr<VisibleGameObject> obj(_factory.newVGO(type, x, y));
	_dynamicObjects->push_back(obj);
}

void GameObjectManager::spawnFire(VisibleGameObject *bomb)
{
	float burnRange = 2;

	float bombX = bomb->getPosition().x;
	float bombY = bomb->getPosition().z;

	float startX = ((bombX - burnRange >= 0) ? bombX - burnRange : 0);
	float startY = ((bombY - burnRange >= 0) ? bombY - burnRange : 0);
	float endX = ((bombX + burnRange < static_cast<float>(_staticObjects[0].size())) ? bombX + burnRange : static_cast<float>(_staticObjects[0].size()));
	float endY = ((bombY + burnRange < static_cast<float>(_staticObjects.size())) ? bombY + burnRange : static_cast<float>(_staticObjects.size()));

	for(float y = startY; y <= endY; y++)
		addDynamicObject(fire, bombX, y);

	for(float x = startX; x <= endX; x++)
	{
		if (x != bombX)
			addDynamicObject(fire, x, bombY);
	}
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
			_dynamicObjects->erase((iter));
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
		if ((*iter)->getType() != type && intersects(box, (*iter)->getBoundingBox()))
		{
			std::cout << "Collides with " << (char)(*iter)->getType() << std::endl;
			return (*iter)->getType();
		}
	}
	return grass;
}

std::vector<std::vector<std::shared_ptr<VisibleGameObject>>> GameObjectManager::_staticObjects;
std::list<std::shared_ptr<VisibleGameObject> > * GameObjectManager::_dynamicObjects;
std::list<std::shared_ptr<VisibleGameObject>> * GameObjectManager::_grass;
ObjectFactory GameObjectManager::_factory;
bool GameObjectManager::_initialized = false;
