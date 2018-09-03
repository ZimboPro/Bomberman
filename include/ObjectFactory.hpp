//
// Created by Patrick RUSSELL on 2018/09/03.
//

#ifndef BOMBERMAN_OBJECTFACTORY_HPP
#define BOMBERMAN_OBJECTFACTORY_HPP

#include "VisibleGameObject.hpp"

class ObjectFactory
{
public:
	enum objectTypes {grass = '0', unbreakableBlocks,
			breakableBlocks, player, enemy1, enemy2,
		powerBlock, healthBlock};
	std::vector<std::vector<VisibleGameObject *>> * genStaticObjects();
	std::list<*VisibleGameObjects> * genDynamicObjects();

};


#endif //BOMBERMAN_OBJECTFACTORY_HPP
