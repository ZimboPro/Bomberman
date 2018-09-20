//
// Created by Patrick RUSSELL on 2018/08/24.
//

#ifndef BOMBERMAN_GAMEOBJECTMANAGER_HPP
#define BOMBERMAN_GAMEOBJECTMANAGER_HPP

#include "game_elements/VisibleGameObject.hpp"
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
	static objectTypes collidesWith(BoundingBox & box);
	static void addDynamicObject(objectTypes type, float x, float y);
	static bool intersects(BoundingBox obj1, BoundingBox obj2);
	static void explodeBomb(VisibleGameObject * bomb);

private:
	static std::vector<std::vector<VisibleGameObject *>> _staticObjects;
	static std::list<std::shared_ptr<VisibleGameObject>> *_dynamicObjects;
	static std::list<std::shared_ptr<VisibleGameObject>> * _grass;
	static ObjectFactory _factory;

};

#endif //BOMBERMAN_GAMEOBJECTMANAGER_HPP
