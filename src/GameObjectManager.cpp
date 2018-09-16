//
// Created by Patrick RUSSELL on 2018/08/24.
//

#include <iostream>
#include "GameObjectManager.hpp"
#include "ObjectFactory.hpp"
#include <glm/vec4.hpp>
#include <Map.hpp>

GameObjectManager::GameObjectManager()
{
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
	std::cout << "=================================" << std::endl;
	Map::printMap();
	std::cout << "=================================" << std::endl;

	for(size_t y = 0; y < _staticObjects.size(); y++) {
		for (size_t x = 0; x < _staticObjects[0].size(); x++)
			std::cout << (char)_staticObjects[y][x]->getType();
		std::cout << std::endl;
	}
}

void GameObjectManager::drawAll(Shaders & shader)
{
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

bool GameObjectManager::intersects(BoundingBox obj1, BoundingBox obj2)
{
	float x1 = obj1.x1;
	float maxX1 = obj1.x2;
	float y1 = obj1.y1;
	float maxY1 = obj1.y2;
	std::cout << x1 << std::endl;

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

objectTypes GameObjectManager::collidesWith(BoundingBox & box)
{
	std::cout << box.x1 << " " << box.x2  << " "<< box.y1  << " "<< box.y2  << " "<< std::endl;
	if (_staticObjects[box.y1][box.x1]->isLoaded())
	{
		std::cout << "Found Static Object1" << std::endl;
		if (_staticObjects[box.y1][box.x1]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}
	else if (_staticObjects[box.y1][box.x2]->isLoaded())
	{
		std::cout << "Found Static Object2" << std::endl;
		if (_staticObjects[box.y2][box.x2]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}
	else if (_staticObjects[box.y2][box.x1]->isLoaded())
	{
		std::cout << "Found Static Object3" << std::endl;
		if (_staticObjects[box.y2][box.x1]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}
	else if (_staticObjects[box.y2][box.x2]->isLoaded())
	{
		std::cout << "Found Static Object4" << std::endl;
		if (_staticObjects[box.y2][box.x2]->isBreakable())
			return objectTypes::breakableBlocks;
		return objectTypes::unbreakableBlocks;
	}

//	for (auto iter = _dynamicObjects->begin(); iter != _dynamicObjects->end(); iter++)
//	{
//		int objX = static_cast<int>((*iter)->getPosition().x);
//		int objY = static_cast<int>((*iter)->getPosition().z);
//
//		if(x == objX && y == objY && type.getType() != (*iter)->getType())
//			return (*iter)->getType();
//	}
	return grass;
}

std::vector<std::vector<VisibleGameObject *>> GameObjectManager::_staticObjects;
std::list<VisibleGameObject *> *GameObjectManager::_dynamicObjects;
std::list<VisibleGameObject *> *GameObjectManager::_grass;
ObjectFactory GameObjectManager::_factory;
