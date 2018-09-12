//
// Created by Patrick RUSSELL on 2018/08/24.
//

#ifndef BOMBERMAN_GAMEOBJECTMANAGER_HPP
#define BOMBERMAN_GAMEOBJECTMANAGER_HPP

#include "VisibleGameObject.hpp"
#include <map>
#include "Shaders.hpp"
#include "ObjectFactory.hpp"
#include "eObjectTypes.hpp"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	static void drawAll(Shaders & shader);
	static void updateAll(float elapsedTime);
	static void init();
	static objectTypes collidesWith(objectTypes type, int x, int y);

private:
	static std::vector<std::vector<VisibleGameObject *>> _staticObjects;
	static std::list<VisibleGameObject *> *_dynamicObjects;
	static std::list<VisibleGameObject *> *_grass;
	static ObjectFactory _factory;
};

#endif //BOMBERMAN_GAMEOBJECTMANAGER_HPP
