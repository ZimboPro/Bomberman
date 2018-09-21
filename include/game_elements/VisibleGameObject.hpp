//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_VISIBLEGAMEOBJECT_HPP
#define BOMBERMAN_VISIBLEGAMEOBJECT_HPP

#include <glm/vec3.hpp>
#include <Window.hpp>
#include "Model_Sprite.hpp"
#include "Shaders.hpp"
#include "eObjectTypes.hpp"
#include "BoundingBox.hpp"
#include <string>

class VisibleGameObject
{
public:
	VisibleGameObject();
	VisibleGameObject(VisibleGameObject const & src);
	virtual ~VisibleGameObject();

	VisibleGameObject(Model_Texture & texture, float x, float y, bool collidable, bool isBreakable);
	virtual void Draw(Shaders & shader);
	virtual void Update(float & elapsedTime);

	virtual void setPosition(float x, float y, float z);
	virtual bool isLoaded() const;
	virtual bool isBreakable() const;
	virtual void setScale(float scale);
	virtual objectTypes getType();
	virtual BoundingBox getBoundingBox();

	virtual glm::vec3 getPosition();

	Model_Sprite getModelSprite();

protected:
	Model_Sprite _model;
	objectTypes _type;
	float _direction;
	BoundingBox _box;

	bool _isLoaded;
	bool _isCollidable;
	bool _isBreakable;
};

#endif //BOMBERMAN_VISIABLEGAMEOBJECT_HPP
