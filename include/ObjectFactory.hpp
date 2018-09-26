//
// Created by Patrick RUSSELL on 2018/09/03.
//

#ifndef BOMBERMAN_OBJECTFACTORY_HPP
#define BOMBERMAN_OBJECTFACTORY_HPP

#include <list>
#include <vector>
#include "game_elements/VisibleGameObject.hpp"
#include "Model_Texture.hpp"
#include "map_generation/Levels.hpp"

#include "game_elements/eObjectTypes.hpp"

class ObjectFactory
{
public:
	ObjectFactory();
	ObjectFactory(ObjectFactory const & src);
	~ObjectFactory();
	std::vector<std::vector<std::shared_ptr<VisibleGameObject>>> genStaticObjects();
	std::list<std::shared_ptr<VisibleGameObject>> * genDynamicAndPickUpObjects();
	std::list<std::shared_ptr<VisibleGameObject>> * genGrass();
	VisibleGameObject * newBomb(float x, float y);
	VisibleGameObject * newVGO(objectTypes type, float x, float y);
	void initModelTextures();

private:

	std::vector<Model_Texture *> _player;
	std::vector<Model_Texture *> _goomba;
	std::vector<Model_Texture *> _koopaTroopa;
	Model_Texture * _unbreakableBlock;
	Model_Texture * _breakableBlock;
	Model_Texture * _powerBlock;
	Model_Texture * _healthBlock;
	Model_Texture * _grass;
	Model_Texture * _bomb;
	Model_Texture * _fire;
	Model_Texture * _pipe;
};

#endif //BOMBERMAN_OBJECTFACTORY_HPP
