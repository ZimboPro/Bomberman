//
// Created by Patrick RUSSELL on 2018/08/23.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include <vector>
#include "VisibleGameObject.hpp"

class Player: public VisibleGameObject
{
public:
	Player();
	Player(Player const & src);
	~Player();

	Player(Model_Texture & texture, float x, float y);
	Player(std::vector<Model_Texture *> & textures, float x, float y);

	void Update(float & timeElapsed);
	virtual void Draw(Shaders & shader);
	BoundingBox getBoundingBox();
	void dropBomb();

	float getVelocity() const;

private:
	void Move(float x, float y);
	void Rotate(float degrees);
	int _index;
	int _prevIndex;
	float _speed;
	float _maxVelocity;
	float _totalElapsed;
	std::vector<Model_Sprite *> _models;
};

#endif //BOMBERMAN_PLAYER_HPP
