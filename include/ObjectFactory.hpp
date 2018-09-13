//
// Created by Patrick RUSSELL on 2018/09/03.
//

#ifndef BOMBERMAN_OBJECTFACTORY_HPP
#define BOMBERMAN_OBJECTFACTORY_HPP

#include <list>
#include "game_elements/VisibleGameObject.hpp"
#include "Model_Texture.hpp"
#include "eObjectTypes.hpp"

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	std::vector<std::vector<VisibleGameObject *>> genStaticObjects();
	std::list<VisibleGameObject *> * genDynamicAndPickUpObjects();
	std::list<VisibleGameObject *> * genGrass();
	VisibleGameObject * newBomb(float x, float y);
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
	Model_Texture * _bomb;
};


#endif //BOMBERMAN_OBJECTFACTORY_HPP
