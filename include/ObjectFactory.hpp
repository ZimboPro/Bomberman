//
// Created by Patrick RUSSELL on 2018/09/03.
//

#ifndef BOMBERMAN_OBJECTFACTORY_HPP
#define BOMBERMAN_OBJECTFACTORY_HPP

#include <list>
#include "VisibleGameObject.hpp"
#include "ModelTexture.hpp"


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
	ModelTexture * _player;
	ModelTexture * _unbreakableBlock;
	ModelTexture * _breakableBlock;
	ModelTexture * _goomba;
	ModelTexture * _koopaTroopa;
	ModelTexture * _powerBlock;
	ModelTexture * _healthBlock;
	ModelTexture * _grass;
};


#endif //BOMBERMAN_OBJECTFACTORY_HPP
