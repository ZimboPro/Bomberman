//
// Created by Patrick RUSSELL on 2018/08/24.
//

#include <iostream>
#include "GameObjectManager.hpp"
#include "ObjectFactory.hpp"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::init()
{
	_factory.initModelTextures();
	_staticObjects = _factory.genStaticObjects();
	_dynamicObjects = _factory.genDynamicAndPickUpObjects();
	_grass = _factory.genGrass();
}

void GameObjectManager::drawAll(Shaders & shader)
{
	for(int y = 0; y < _staticObjects.size(); y++)
		for (int x = 0; x < _staticObjects[y].size(); x++)
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

std::vector<std::vector<VisibleGameObject *>> GameObjectManager::_staticObjects;
std::list<VisibleGameObject *> *GameObjectManager::_dynamicObjects;
std::list<VisibleGameObject *> *GameObjectManager::_grass;
ObjectFactory GameObjectManager::_factory;
