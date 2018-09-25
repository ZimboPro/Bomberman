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
	GameObjectManager(GameObjectManager const & src);
	~GameObjectManager();

	static void drawAll(Shaders & shader);
	static void updateAll(float elapsedTime);
	static void init();
	static objectTypes collidesWith(BoundingBox & box, objectTypes type);
	static void addDynamicObject(objectTypes type, float x, float y);
	static void explodeBomb(VisibleGameObject * bomb);
	static void removeDynamicObject(VisibleGameObject * obj);
	static void newLevel( int type );
	static bool setFireAndContinue(float x, float y);
	static void removePickup(float x, float y);

private:
	static void clearLevelUp();
	static void clearLevelDown();
	static void initLevel();
	static bool intersects(BoundingBox obj1, BoundingBox obj2);
	static void spawnFire(VisibleGameObject *bomb);
	static std::vector<std::vector<std::shared_ptr<VisibleGameObject>>> _staticObjects;
	static std::list<std::shared_ptr<VisibleGameObject>> *_dynamicObjects;
	static std::list<std::shared_ptr<VisibleGameObject>> * _grass;
	static ObjectFactory _factory;
	static bool _initialized;

};

#endif //BOMBERMAN_GAMEOBJECTMANAGER_HPP
