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
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::add(std::string name, VisibleGameObject * gameObject)
{
	_gameObjects.insert(std::make_pair(name, gameObject));
}

void GameObjectManager::remove(const std::string & name)
{
	auto result = _gameObjects.find(name);
	if(result != _gameObjects.end())
	{
		delete result->second;
		_gameObjects.erase(result);
	}
}

void GameObjectManager::init()
{
	_factory.initModelTextures();
	_staticObjects = _factory.genStaticObjects();
	_dynamicObjects = _factory.genDynamicAndPickUpObjects();
}

int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}

VisibleGameObject * GameObjectManager::get(const std::string & name) const
{
	auto result = _gameObjects.find(name);
	if (result != _gameObjects.end())
		return result->second;
	return nullptr;
}

void GameObjectManager::drawAll(Shaders & shader)
{
	for(int y = 0; y < _staticObjects.size(); y++)
	{
		for (int x = 0; x < _staticObjects[y].size(); x++)
		{
			_staticObjects[y][x]->Draw(shader);
		}
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

void GameObjectManager::GameObjectDeallocator::operator()(const std::pair<std::string, VisibleGameObject *> & p) const
{
	delete p.second;
}
