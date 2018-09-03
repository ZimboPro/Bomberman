//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_VISIBLEGAMEOBJECT_HPP
#define BOMBERMAN_VISIBLEGAMEOBJECT_HPP

#include <Window.hpp>
#include "Models.hpp"
#include "Shaders.hpp"
#include <string>

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	VisibleGameObject(Shaders *shader, Model *model, float x, float y);
	virtual void Load(std::string fileName);
	virtual void Draw();
	virtual void Update(float & elapsedTime);

	virtual void setShader(Shader *shader);
	virtual void setModel(Model *model);

	virtual void setPosition(int x, int y);
	virtual bool isLoaded() const;

	virtual float getWidth();
	virtual float getHeight();

protected:

private:
	Model *_model;
	Shaders *_shader;
	bool _isLoaded;
	float _x;
	float _y;
};

#endif //BOMBERMAN_VISIABLEGAMEOBJECT_HPP
