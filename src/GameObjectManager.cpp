//
// Created by Patrick RUSSELL on 2018/08/24.
//

#include <iostream>
#include "GameObjectManager.hpp"

GameObjectManager::GameObjectManager() = default;

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
	auto iter = _gameObjects.begin();
	while(iter != _gameObjects.end())
	{
		iter->second->Draw(shader);
		iter++;
	}
}

void GameObjectManager::updateAll(float elapsedTime)
{
	auto iter = _gameObjects.begin();
	while(iter != _gameObjects.end())
	{
		iter->second->Update(elapsedTime);
		iter++;
	}
}

void GameObjectManager::GameObjectDeallocator::operator()(const std::pair<std::string, VisibleGameObject *> & p) const
{
	delete p.second;
}
