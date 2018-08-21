//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_VISIBLEGAMEOBJECT_HPP
#define BOMBERMAN_VISIBLEGAMEOBJECT_HPP

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string fileName);
	virtual void Draw(sf::Window & window);

	virtual void setPosition(int x, int y);

private:
	sf::Sprite _sprite;
	sf::texture _texture;
	std::string _filename;
	bool _isLoaded;
};

#endif //BOMBERMAN_VISIABLEGAMEOBJECT_HPP
