//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_VISIBLEGAMEOBJECT_HPP
#define BOMBERMAN_VISIBLEGAMEOBJECT_HPP

#include <glm/vec2.hpp>
#include <Window.hpp>
#include "Models.hpp"
#include "Shaders.hpp"
#include <string>

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	VisibleGameObject(Model *model, Shaders *shader, float y, float x, bool collidable);
	virtual void Draw();
	virtual void Update(float & elapsedTime);

	virtual void setShader(Shaders *shader);
	virtual void setModel(Model *model);

	virtual void setPosition(int y, int x);
	virtual bool isLoaded() const;

	virtual glm::vec2 getPosition();

protected:

private:
	Model *_model;
	Shaders *_shader;
	bool _isLoaded;
	glm::vec2 _position;
	bool _isCollidable;
};

#endif //BOMBERMAN_VISIABLEGAMEOBJECT_HPP
