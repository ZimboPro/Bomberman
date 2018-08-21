//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject()
{
	this->_isLoaded = false;
}

virtual ~VisibleGameObject() {}

virtual void Load(std::string fileName)
{

}

virtual void Draw(sf::Window & window);

virtual void setPosition(int x, int y);
