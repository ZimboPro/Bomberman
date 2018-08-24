//
// Created by Patrick RUSSELL on 2018/08/24.
//

#include "GameObjectManager.hpp"


GameObjectManager::GameObjectManager() {}

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
	std::map<std::string, VisibleGameObject *>::iterator result = _gameObjects.find(name);
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
	std::map<std::string, VisibleGameObject *>::const_iterator result = _gameObjects.find(name);
	if (result != _gameObjects.end())
		return result->second;
	return NULL;
}

void GameObjectManager::drawAll(sf::RenderWindow & window)
{
	std::map<std::string, VisibleGameObject *>::const_iterator iter = _gameObjects.begin();
	while(iter != _gameObjects.end())
	{
		iter->second->Draw(window);
		iter++;
	}
}

void GameObjectManager::GameObjectDeallocator::operator()(const std::pair<std::string, VisibleGameObject *> & p) const
{
	delete p.second;
}

/*
struct GameObjectDeallocator
{
	void operator()(const std::pair<std::string, VisibleGameObject *> & p) const
	{
		delete p.second;
	}
};
*/