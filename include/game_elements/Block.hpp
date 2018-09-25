#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "VisibleGameObject.hpp"

class Block: public VisibleGameObject
{
public:
	Block();
	Block(Block const & src);
	Block(Model_Texture & texture, float x, float y, bool isBreakable);
	~Block();
	BoundingBox getBoundingBox();
	void Update(float & elapsedTime);

private:
	void dying(float & elapsedTime);
};

#endif