//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_VISIBLEGAMEOBJECT_HPP
#define BOMBERMAN_VISIBLEGAMEOBJECT_HPP

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string fileName);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float elapsedTime);

	virtual void setPosition(int x, int y);
	virtual sf::Vector2f getPosition() const;
	virtual bool isLoaded() const;

protected:
	sf::CircleShape & getSprite();

private:
	sf::CircleShape _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
};

#endif //BOMBERMAN_VISIABLEGAMEOBJECT_HPP
