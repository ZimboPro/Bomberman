//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_VISIBLEGAMEOBJECT_HPP
#define BOMBERMAN_VISIBLEGAMEOBJECT_HPP

#include <glm/vec3.hpp>
#include <Window.hpp>
#include "Model_Sprite.hpp"
#include "Shaders.hpp"
#include <string>

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	VisibleGameObject(Model_Texture & texture, float x, float y, bool collidable, bool isBreakable);
	virtual void Draw(Shaders & shader);
	virtual void Update(float & elapsedTime);

	virtual void setPosition(float x, float y, float z);
	virtual bool isLoaded() const;
	virtual bool isBreakable() const;
	virtual void setScale(float scale);

	virtual glm::vec3 getPosition();

	Model_Sprite getModelSprite();

private:
	Model_Sprite _model;
	bool _isLoaded;
	int _direction;
	bool _isCollidable;
	bool _isBreakable;
};

#endif //BOMBERMAN_VISIABLEGAMEOBJECT_HPP
