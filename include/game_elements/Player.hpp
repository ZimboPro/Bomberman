//
// Created by Patrick RUSSELL on 2018/08/23.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include <vector>
#include "VisibleGameObject.hpp"
#include "ServiceLocator.hpp"

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
	virtual Rectangle getBoundBox();

private:
	void Move(float x, float y, float z = 0);
	void Rotate(float degrees);
	void fixCameraPosition();
	void init();
	void movement(float degree, float x, float y, float x1, float y1, float camX, float camY, BoundingBox & box, objectTypes &collidesWith, float timeElapsed);
	void checks(float &timeElapsed);
	void placeBombX(float & bombX, float & bombY, float bombOffset, float moveX, float moveY, float pos, bool ceil);
	void placeBombY(float & bombX, float & bombY, float bombOffset, float moveX, float moveY, float pos, bool ceil);
	void aboutToDie();

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
	IAudioProvider * _sound;
};

#endif //BOMBERMAN_PLAYER_HPP
