//
// Created by Patrick RUSSELL on 2018/09/03.
//

#ifndef BOMBERMAN_OBJECTFACTORY_HPP
#define BOMBERMAN_OBJECTFACTORY_HPP

#include <list>
#include "VisibleGameObject.hpp"
#include "Model_Texture.hpp"
#include "../src/Map_Gen/Levels.hpp"



class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	enum objectTypes {grass = '0', unbreakableBlocks,
			breakableBlocks, player, goomba, koopaTroopa,
		powerBlock, healthBlock};
	std::vector<std::vector<VisibleGameObject *>> genStaticObjects();
	std::list<VisibleGameObject *> * genDynamicAndPickUpObjects();
	void initModelTextures();

private:
	Model_Texture * _player;
	Model_Texture * _unbreakableBlock;
	Model_Texture * _breakableBlock;
	Model_Texture * _goomba;
	Model_Texture * _koopaTroopa;
	Model_Texture * _powerBlock;
	Model_Texture * _healthBlock;
	Model_Texture * _grass;
};

#endif //BOMBERMAN_OBJECTFACTORY_HPP
