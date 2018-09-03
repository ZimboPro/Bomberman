//
// Created by Patrick RUSSELL on 2018/08/24.
//

#ifndef BOMBERMAN_GAMEOBJECTMANAGER_HPP
#define BOMBERMAN_GAMEOBJECTMANAGER_HPP

#include "VisibleGameObject.hpp"
#include <map>
#include "Shaders.hpp"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, VisibleGameObject * gameObject);
	void remove(const std::string & name);
	int getObjectCount() const;
	VisibleGameObject * get(const std::string & name) const;
	void drawAll(Shaders & shader);
	void updateAll(float elapsedTime);

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject *> & p) const;
	};
};

#endif //BOMBERMAN_GAMEOBJECTMANAGER_HPP
