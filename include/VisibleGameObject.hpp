//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_VISIBLEGAMEOBJECT_HPP
#define BOMBERMAN_VISIBLEGAMEOBJECT_HPP

#include <glm/vec3.hpp>
#include <Window.hpp>
#include "Models.hpp"
#include "Shaders.hpp"
#include <string>

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	VisibleGameObject(Model *model, float x, float y, bool collidable);
	virtual void Draw(Shaders & shader);
	virtual void Update(float & elapsedTime);

	virtual void setModel(Model *model);

	virtual void setPosition(float x, float y, float z);
	virtual bool isLoaded() const;
	virtual bool isBreakable() const;

	virtual glm::vec3 getPosition();


protected:
	Model * getModel();

private:
	Model *_model;
	bool _isLoaded;
	glm::vec3 _position;
	int _direction;
	bool _isCollidable;
	bool _isBreakable;
};

#endif //BOMBERMAN_VISIABLEGAMEOBJECT_HPP
