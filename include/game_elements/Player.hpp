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
	void dying(float & timeElapsed);
	void setCamera();

private:
	void Move(float x, float y, float z = 0);
	void Rotate(float degrees);
	void fixCameraPosition();

	int _index;
	int _prevIndex;
	float _speed;
	float _totalElapsed;
	float _totalDroppedWhilstDying;
	bool _wonLevel;
	bool _spawn;
	bool _spawned;
	float _timeSpawned;
	std::vector<Model_Sprite *> _models;
};

#endif //BOMBERMAN_PLAYER_HPP
