//
// Created by Patrick RUSSELL on 2018/09/03.
//

#ifndef BOMBERMAN_OBJECTFACTORY_HPP
#define BOMBERMAN_OBJECTFACTORY_HPP

#include <list>
#include "VisibleGameObject.hpp"


class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	enum objectTypes {grass = '0', unbreakableBlocks,
			breakableBlocks, player, goomba, koopaTroopa,
		powerBlock, healthBlock};
	std::vector<std::vector<VisibleGameObject *>> * genStaticObjects();
	std::list<VisibleGameObject *> * genDynamicAndPickUpObjects();

private:
	Model *_player;
	Model *_unbreakableBlock;
	Model *_breakableBlock;
	Model *_goomba;
	Model *_koopaTroopa;
	Model *_powerBlock;
	Model *_healthBlock;
};


#endif //BOMBERMAN_OBJECTFACTORY_HPP
